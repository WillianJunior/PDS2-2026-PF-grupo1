$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
if (Get-Variable -Name PSNativeCommandUseErrorActionPreference -ErrorAction SilentlyContinue) {
	$PSNativeCommandUseErrorActionPreference = $false
}

function Test-CommandExists {
	param([string]$CommandName)
	return $null -ne (Get-Command $CommandName -ErrorAction SilentlyContinue)
}

function Get-KnownCommandPaths {
	param([string]$CommandName)

	return @(
		(Join-Path $env:ProgramFiles "CMake\bin\$CommandName.exe"),
		(Join-Path ${env:ProgramFiles(x86)} "CMake\bin\$CommandName.exe"),
		(Join-Path $env:LOCALAPPDATA "Programs\CMake\bin\$CommandName.exe"),
		"C:\msys64\ucrt64\bin\$CommandName.exe",
		"C:\msys64\mingw64\bin\$CommandName.exe",
		"C:\msys64\usr\bin\$CommandName.exe"
	)
}

function Get-CommandPathOrNull {
	param([string]$CommandName)

	$command = Get-Command $CommandName -ErrorAction SilentlyContinue
	if ($null -ne $command) {
		return $command.Source
	}

	foreach ($candidate in (Get-KnownCommandPaths -CommandName $CommandName)) {
		if ((-not [string]::IsNullOrWhiteSpace($candidate)) -and (Test-Path $candidate)) {
			return $candidate
		}
	}

	return $null
}

function Get-PreferredCMakePathOrNull {
	foreach ($candidate in (Get-KnownCommandPaths -CommandName 'cmake')) {
		if ((-not [string]::IsNullOrWhiteSpace($candidate)) -and (Test-Path $candidate) -and ($candidate -notlike 'C:\msys64\*')) {
			return $candidate
		}
	}

	$command = Get-Command cmake -ErrorAction SilentlyContinue
	if ($null -ne $command) {
		return $command.Source
	}

	foreach ($candidate in (Get-KnownCommandPaths -CommandName 'cmake')) {
		if ((-not [string]::IsNullOrWhiteSpace($candidate)) -and (Test-Path $candidate)) {
			return $candidate
		}
	}

	return $null
}

function Add-ToolDirectoryToPath {
	param([string]$ToolPath)

	if ([string]::IsNullOrWhiteSpace($ToolPath)) {
		return
	}

	$toolDirectory = Split-Path -Parent $ToolPath
	if ($env:PATH -notlike "*$toolDirectory*") {
		$env:PATH = "$toolDirectory;$env:PATH"
	}
}

function Invoke-Step {
	param(
		[string]$Command,
		[string[]]$Arguments,
		[string]$Description
	)

	Write-Host "[test]  $Description" -ForegroundColor Cyan
	Write-Host "[info]  $Command $($Arguments -join ' ')" -ForegroundColor Gray

	& $Command @Arguments
	$exitCode = $LASTEXITCODE
	if ($exitCode -ne 0) {
		throw ("Failed to run '{0}'. Exit code: {1}" -f $Command, $exitCode)
	}
}

function Resolve-ToolchainArguments {
	$ninjaPath = Get-CommandPathOrNull 'ninja'
	$mingwMakePath = Get-CommandPathOrNull 'mingw32-make'
	$gccPath = Get-CommandPathOrNull 'gcc'
	$gxxPath = Get-CommandPathOrNull 'g++'

	if (($null -ne $ninjaPath) -and ($null -ne $gccPath) -and ($null -ne $gxxPath)) {
		Add-ToolDirectoryToPath -ToolPath $ninjaPath
		Add-ToolDirectoryToPath -ToolPath $gccPath
		Add-ToolDirectoryToPath -ToolPath $gxxPath
		return @(
			'-G', 'Ninja',
			("-DCMAKE_MAKE_PROGRAM={0}" -f $ninjaPath),
			("-DCMAKE_C_COMPILER={0}" -f $gccPath),
			("-DCMAKE_CXX_COMPILER={0}" -f $gxxPath)
		)
	}

	if (($null -ne $mingwMakePath) -and ($null -ne $gccPath) -and ($null -ne $gxxPath)) {
		Add-ToolDirectoryToPath -ToolPath $mingwMakePath
		Add-ToolDirectoryToPath -ToolPath $gccPath
		Add-ToolDirectoryToPath -ToolPath $gxxPath
		return @(
			'-G', 'MinGW Makefiles',
			("-DCMAKE_MAKE_PROGRAM={0}" -f $mingwMakePath),
			("-DCMAKE_C_COMPILER={0}" -f $gccPath),
			("-DCMAKE_CXX_COMPILER={0}" -f $gxxPath)
		)
	}

	throw 'Could not detect a GCC-based toolchain required for gcovr coverage.'
}

function Get-SelectedGenerator {
	param([string[]]$Arguments)

	for ($i = 0; $i -lt $Arguments.Count - 1; $i++) {
		if ($Arguments[$i] -eq '-G') {
			return $Arguments[$i + 1]
		}
	}

	return $null
}

function Get-CachedGenerator {
	param([string]$BuildDirectory)

	$cachePath = Join-Path $BuildDirectory 'CMakeCache.txt'
	if (-not (Test-Path $cachePath)) {
		return $null
	}

	$line = Get-Content $cachePath | Where-Object { $_ -like 'CMAKE_GENERATOR:INTERNAL=*' } | Select-Object -First 1
	if ([string]::IsNullOrWhiteSpace($line)) {
		return $null
	}

	return ($line -replace '^CMAKE_GENERATOR:INTERNAL=', '')
}

function Clear-CMakeConfigureCache {
	param([string]$BuildDirectory)

	$cacheFile = Join-Path $BuildDirectory 'CMakeCache.txt'
	$cacheDir = Join-Path $BuildDirectory 'CMakeFiles'

	if (Test-Path $cacheFile) {
		Remove-Item $cacheFile -Force
	}

	if (Test-Path $cacheDir) {
		Remove-Item $cacheDir -Recurse -Force
	}
}

function Convert-ToForwardSlashPath {
	param([string]$PathValue)

	return ($PathValue -replace '\\', '/')
}

$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectRoot = Split-Path -Parent $scriptDirectory
$buildDirectory = Join-Path $projectRoot 'build'
$coverageDirectory = Join-Path $projectRoot 'coverage'

Set-Location $projectRoot

	$cmakeExecutable = Get-PreferredCMakePathOrNull
if ($null -eq $cmakeExecutable) {
	throw 'CMake was not found in PATH.'
}

if ($null -eq (Get-Command gcovr -ErrorAction SilentlyContinue)) {
	throw 'gcovr was not found in PATH.'
}

$ctestExecutable = Join-Path (Split-Path -Parent $cmakeExecutable) 'ctest.exe'
if (-not (Test-Path $ctestExecutable)) {
	$ctestCommand = Get-Command ctest -ErrorAction SilentlyContinue
	if ($null -eq $ctestCommand) {
		throw 'ctest was not found in PATH.'
	}

	$ctestExecutable = $ctestCommand.Source
}

Write-Host "[info]  CMake em uso: $cmakeExecutable" -ForegroundColor Gray
Write-Host "[info]  CTest em uso: $ctestExecutable" -ForegroundColor Gray

$gcovrRootPath = Convert-ToForwardSlashPath -PathValue $projectRoot
$gcovrFilterPath = Convert-ToForwardSlashPath -PathValue (Join-Path $projectRoot 'src')
$gcovrHtmlPath = Convert-ToForwardSlashPath -PathValue (Join-Path $coverageDirectory 'index.html')
$gcovrXmlPath = Convert-ToForwardSlashPath -PathValue (Join-Path $coverageDirectory 'coverage.xml')

$toolchainArguments = Resolve-ToolchainArguments
$selectedGenerator = Get-SelectedGenerator -Arguments $toolchainArguments
$cachedGenerator = Get-CachedGenerator -BuildDirectory $buildDirectory
if (($null -ne $selectedGenerator) -and ($null -ne $cachedGenerator) -and ($selectedGenerator -ne $cachedGenerator)) {
	Clear-CMakeConfigureCache -BuildDirectory $buildDirectory
}

Invoke-Step -Command $cmakeExecutable -Arguments (@('-S', $projectRoot, '-B', $buildDirectory, '-DENABLE_COVERAGE=ON') + $toolchainArguments) -Description 'Configuring tests with coverage'
Invoke-Step -Command $cmakeExecutable -Arguments @('--build', $buildDirectory, '--config', 'Debug', '--target', 'edu_social_tests') -Description 'Building unit tests'
Invoke-Step -Command $ctestExecutable -Arguments @('--test-dir', $buildDirectory, '--output-on-failure', '--build-config', 'Debug') -Description 'Running unit tests'

New-Item -ItemType Directory -Force -Path $coverageDirectory | Out-Null

Invoke-Step -Command 'gcovr' -Arguments @(
	'--root', $gcovrRootPath,
	'--filter', $gcovrFilterPath,
	'--html-details', $gcovrHtmlPath,
	'--xml', $gcovrXmlPath,
	'--print-summary'
) -Description 'Generating coverage reports'
