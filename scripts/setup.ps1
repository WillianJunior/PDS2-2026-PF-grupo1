$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'

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

function Ensure-CMake {
	Write-Step 'Validando CMake no ambiente'

	$cmakePath = Get-CommandPathOrNull 'cmake'
	if ($null -eq $cmakePath) {
		Write-Fail 'CMake was not found in PATH.'
		Write-Info 'Install CMake and open a new terminal before running this script again.'
		throw 'CMake was not found.'
	}

	Add-ToolDirectoryToPath -ToolPath $cmakePath
	$versionLine = (& $cmakePath --version | Select-Object -First 1)
	Write-Info ("CMake encontrado: {0}" -f $versionLine)
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

function Clear-CMakeConfigureCache {
	param([string]$BuildDirectory)

	Write-Step 'Limpando cache de configuracao do CMake'

	$cacheFile = Join-Path $BuildDirectory 'CMakeCache.txt'
	$cacheDir = Join-Path $BuildDirectory 'CMakeFiles'

	if (Test-Path $cacheFile) {
		Remove-Item $cacheFile -Force
		Write-Info 'Arquivo removido: build/CMakeCache.txt'
	}

	if (Test-Path $cacheDir) {
		Remove-Item $cacheDir -Recurse -Force
		Write-Info 'Diretorio removido: build/CMakeFiles'
	}
}

function Ensure-LocalIntelliSenseConfig {
	param([string]$ProjectRoot)

	$vscodeDir = Join-Path $ProjectRoot '.vscode'
	$configPath = Join-Path $vscodeDir 'c_cpp_properties.json'

	Write-Step 'Garantindo configuracao local do IntelliSense'
	if (Test-Path $configPath) {
		Write-Info 'c_cpp_properties.json ja existe. Nenhuma alteracao necessaria.'
		return
	}

	New-Item -ItemType Directory -Force -Path $vscodeDir | Out-Null

	$json = @'
{
	"configurations": [
		{
			"name": "Win32",
			"includePath": [
				"${workspaceFolder}/include",
				"${workspaceFolder}/build/_deps/sqlite_amalgamation-src",
				"${workspaceFolder}/build/_deps/crow-src/include",
				"${workspaceFolder}/build/_deps/asio-src/asio/include"
			],
			"defines": [],
			"compileCommands": "${workspaceFolder}/build/compile_commands.json",
			"cppStandard": "c++17",
			"cStandard": "c17",
			"intelliSenseMode": "windows-msvc-x64"
		}
	],
	"version": 4
}
'@

	Set-Content -Path $configPath -Value $json -Encoding UTF8
	Write-Info 'Arquivo .vscode/c_cpp_properties.json criado.'
}

try {
	$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
	$projectRoot = Split-Path -Parent $scriptDirectory
	$buildDirectory = Join-Path $projectRoot 'build'
	$binaryPath = Join-Path $buildDirectory 'bin\edu_social_backend.exe'

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
		Clear-CMakeConfigureCache -BuildDirectory $buildDirectory
	}

	$configureArguments = @('-S', $projectRoot, '-B', $buildDirectory) + $toolchainArguments
	Invoke-ExternalCommand -Command $cmakeExecutable -Arguments $configureArguments -Description 'Configurando projeto com CMake'

	Ensure-LocalIntelliSenseConfig -ProjectRoot $projectRoot

	Invoke-ExternalCommand -Command $cmakeExecutable -Arguments @('--build', $buildDirectory, '--config', 'Debug') -Description 'Compilando binario'

	if (-not (Test-Path $binaryPath)) {
		throw ("Binary was not found after compilation: {0}" -f $binaryPath)
	}

	Write-Step 'Inicializando servidor'
	Write-Info ("Executavel: {0}" -f $binaryPath)
	Write-Info 'Endpoint health esperado: http://localhost:18080/health'
	& $binaryPath
}
catch {
	Write-Fail $_.Exception.Message
	exit 1
}
