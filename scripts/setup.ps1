$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
if (Get-Variable -Name PSNativeCommandUseErrorActionPreference -ErrorAction SilentlyContinue) {
	$PSNativeCommandUseErrorActionPreference = $false
}

function Write-Step {
	param([string]$Message)
	Write-Host "[setup] $Message" -ForegroundColor Cyan
}

function Write-Info {
	param([string]$Message)
	Write-Host "[info]  $Message" -ForegroundColor Gray
}

function Write-Fail {
	param([string]$Message)
	Write-Host "[error] $Message" -ForegroundColor Red
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

function Invoke-ExternalCommand {
	param(
		[string]$Command,
		[string[]]$Arguments,
		[string]$Description
	)

	Write-Step $Description
	Write-Info ("Executando: {0} {1}" -f $Command, ($Arguments -join ' '))

	& $Command @Arguments
	$exitCode = $LASTEXITCODE
	if ($exitCode -ne 0) {
		throw ("Failed to run '{0}'. Exit code: {1}" -f $Command, $exitCode)
	}
}

function Clear-FetchContentSubbuilds {
	param([string]$BuildDirectory)

	$depsDirectory = Join-Path $BuildDirectory '_deps'
	if (-not (Test-Path $depsDirectory)) {
		return
	}

	$subbuildDirectories = Get-ChildItem -Path $depsDirectory -Directory -Filter '*-subbuild' -ErrorAction SilentlyContinue
	foreach ($directory in $subbuildDirectories) {
		Remove-Item -LiteralPath $directory.FullName -Recurse -Force
		Write-Info ("Removed stale FetchContent subbuild: {0}" -f $directory.Name)
	}
}

function Ensure-CMake {
	Write-Step 'Validando CMake no ambiente'

	$cmakePath = Get-PreferredCMakePathOrNull
	if ($null -eq $cmakePath) {
		Write-Fail 'CMake was not found in PATH.'
		Write-Info 'Install CMake and open a new terminal before running this script again.'
		throw 'CMake was not found.'
	}

	Add-ToolDirectoryToPath -ToolPath $cmakePath
	$versionLine = (& $cmakePath --version | Select-Object -First 1)
	Write-Info ("CMake encontrado: {0}" -f $versionLine)
	Write-Info ("CMake em uso: {0}" -f $cmakePath)
	return $cmakePath
}

function Resolve-ToolchainArguments {
	Write-Step 'Detectando gerador e compilador C/C++'

	$ninjaPath = Get-CommandPathOrNull 'ninja'
	$mingwMakePath = Get-CommandPathOrNull 'mingw32-make'
	$gccPath = Get-CommandPathOrNull 'gcc'
	$gxxPath = Get-CommandPathOrNull 'g++'
	$nmakePath = Get-CommandPathOrNull 'nmake'
	$clPath = Get-CommandPathOrNull 'cl'

	Write-Info ("ninja: {0}" -f ($(if ($ninjaPath) { $ninjaPath } else { 'NAO_ENCONTRADO' })))
	Write-Info ("mingw32-make: {0}" -f ($(if ($mingwMakePath) { $mingwMakePath } else { 'NAO_ENCONTRADO' })))
	Write-Info ("gcc: {0}" -f ($(if ($gccPath) { $gccPath } else { 'NAO_ENCONTRADO' })))
	Write-Info ("g++: {0}" -f ($(if ($gxxPath) { $gxxPath } else { 'NAO_ENCONTRADO' })))
	Write-Info ("nmake: {0}" -f ($(if ($nmakePath) { $nmakePath } else { 'NAO_ENCONTRADO' })))
	Write-Info ("cl: {0}" -f ($(if ($clPath) { $clPath } else { 'NAO_ENCONTRADO' })))

	if (($null -ne $ninjaPath) -and ($null -ne $gccPath) -and ($null -ne $gxxPath)) {
		Add-ToolDirectoryToPath -ToolPath $ninjaPath
		Add-ToolDirectoryToPath -ToolPath $gccPath
		Add-ToolDirectoryToPath -ToolPath $gxxPath
		Write-Info 'Estrategia selecionada: Ninja + GCC/G++'
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
		Write-Info 'Estrategia selecionada: MinGW Makefiles + GCC/G++'
		return @(
			'-G', 'MinGW Makefiles',
			("-DCMAKE_MAKE_PROGRAM={0}" -f $mingwMakePath),
			("-DCMAKE_C_COMPILER={0}" -f $gccPath),
			("-DCMAKE_CXX_COMPILER={0}" -f $gxxPath)
		)
	}

	if (($null -ne $nmakePath) -and ($null -ne $clPath)) {
		Write-Info 'Estrategia selecionada: NMake Makefiles + MSVC'
		return @('-G', 'NMake Makefiles')
	}

	throw 'Could not detect a valid C/C++ toolchain. Install MinGW/GCC, Ninja, or Visual Studio Build Tools.'
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

function Clear-BuildArtifacts {
	param([string]$BuildDirectory)

	Write-Step 'Cleaning build artifacts for generator switch'

	if (-not (Test-Path $BuildDirectory)) {
		return
	}

	Get-ChildItem -Force -Path $BuildDirectory | Where-Object { $_.Name -ne '.gitkeep' } | Remove-Item -Recurse -Force
	Write-Info 'Removed generated contents from build/'
}

function Invoke-CMakeConfigure {
	param(
		[string]$CMakeExecutable,
		[string[]]$Arguments,
		[string]$BuildDirectory
	)

	Write-Step 'Configurando projeto com CMake'
	Write-Info ("Executando: {0} {1}" -f $CMakeExecutable, ($Arguments -join ' '))
	Write-Info 'Dependency resolution may take some time during the first configure step.'

	Clear-FetchContentSubbuilds -BuildDirectory $BuildDirectory

	$logPath = Join-Path $BuildDirectory 'cmake-configure.log'
	if (Test-Path $logPath) {
		Remove-Item -LiteralPath $logPath -Force
	}

	$commandOutput = @()
	& $CMakeExecutable @Arguments 2>&1 |
		ForEach-Object { $_.ToString() } |
		Tee-Object -FilePath $logPath |
		Tee-Object -Variable commandOutput | Out-Host
	$exitCode = $LASTEXITCODE

	if ($exitCode -eq 0) {
		return
	}

	$joinedOutput = ($commandOutput | Out-String)
	if ($joinedOutput -like '*Does not match the generator used previously*') {
		Write-Info 'Generator mismatch detected during configure. Cleaning build directory and retrying once.'
		Clear-BuildArtifacts -BuildDirectory $BuildDirectory

		$retryOutput = @()
		& $CMakeExecutable @Arguments 2>&1 |
			ForEach-Object { $_.ToString() } |
			Tee-Object -FilePath $logPath |
			Tee-Object -Variable retryOutput | Out-Host
		$retryExitCode = $LASTEXITCODE

		if ($retryExitCode -eq 0) {
			return
		}

		if ((($retryOutput | Out-String)) -like '*Could not connect to server*') {
			Write-Info 'Dependency download failed. Check network access to github.com and sqlite.org.'
		}

		throw ("Failed to run '{0}'. Exit code: {1}" -f $CMakeExecutable, $retryExitCode)
	}

	if ($joinedOutput -like '*Could not connect to server*') {
		Write-Info 'Dependency download failed. Check network access to github.com and sqlite.org.'
	}

	throw ("Failed to run '{0}'. Exit code: {1}" -f $CMakeExecutable, $exitCode)
}

try {
	$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
	$projectRoot = Split-Path -Parent $scriptDirectory
	$buildDirectory = Join-Path $projectRoot 'build'

	Write-Step 'Bootstrap iniciado'
	Write-Info ("Data/Hora: {0}" -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'))
	Write-Info ("Projeto:   {0}" -f $projectRoot)
	Write-Info ("Build dir: {0}" -f $buildDirectory)

	Set-Location $projectRoot

	$cmakeExecutable = Ensure-CMake
	$toolchainArguments = Resolve-ToolchainArguments

	$selectedGenerator = Get-SelectedGenerator -Arguments $toolchainArguments
	$cachedGenerator = Get-CachedGenerator -BuildDirectory $buildDirectory
	if (($null -ne $selectedGenerator) -and ($null -ne $cachedGenerator) -and ($selectedGenerator -ne $cachedGenerator)) {
		Write-Info ("Gerador em cache detectado: {0}" -f $cachedGenerator)
		Write-Info ("Gerador atual selecionado: {0}" -f $selectedGenerator)
		Clear-BuildArtifacts -BuildDirectory $buildDirectory
	}

	$configureArguments = @(
		'-S', $projectRoot,
		'-B', $buildDirectory
	) + $toolchainArguments
	Invoke-CMakeConfigure -CMakeExecutable $cmakeExecutable -Arguments $configureArguments -BuildDirectory $buildDirectory

	Invoke-ExternalCommand -Command $cmakeExecutable -Arguments @('--build', $buildDirectory, '--config', 'Debug') -Description 'Compilando binario'
	Write-Step 'Bootstrap finalizado'
	Write-Info 'Use scripts/run.ps1 or make serve to start the server.'
}
catch {
	Write-Fail $_.Exception.Message
	exit 1
}
