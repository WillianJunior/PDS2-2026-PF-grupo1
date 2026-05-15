$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'

function Write-Step {
	param([string]$Message)
	Write-Host "[docs]  $Message" -ForegroundColor Cyan
}

function Write-Info {
	param([string]$Message)
	Write-Host "[info]  $Message" -ForegroundColor Gray
}

function Write-Fail {
	param([string]$Message)
	Write-Host "[error] $Message" -ForegroundColor Red
}

function Resolve-DoxygenCommand {
	$command = Get-Command doxygen -ErrorAction SilentlyContinue
	if ($null -ne $command) {
		return $command.Source
	}

	$candidates = @(
		(Join-Path $env:ProgramFiles 'doxygen\bin\doxygen.exe'),
		(Join-Path ${env:ProgramFiles(x86)} 'doxygen\bin\doxygen.exe'),
		'C:\msys64\ucrt64\bin\doxygen.exe',
		'C:\msys64\mingw64\bin\doxygen.exe',
		'C:\msys64\usr\bin\doxygen.exe'
	)

	foreach ($candidate in $candidates) {
		if ((-not [string]::IsNullOrWhiteSpace($candidate)) -and (Test-Path $candidate)) {
			return $candidate
		}
	}

	return $null
}

try {
	$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
	$projectRoot = Split-Path -Parent $scriptDirectory
	$doxyfilePath = Join-Path $projectRoot 'Doxyfile'
	$doxygenPath = Resolve-DoxygenCommand

	if ($null -eq $doxygenPath) {
		Write-Fail 'Doxygen was not found in PATH.'
		Write-Info 'Install Doxygen and open a new terminal before running this script again.'
		exit 1
	}

	if (-not (Test-Path $doxyfilePath)) {
		Write-Fail 'Doxyfile was not found in the project root.'
		exit 1
	}

	Set-Location $projectRoot
	Write-Step 'Generating documentation with Doxygen'
	Write-Info ("Command: {0} {1}" -f $doxygenPath, $doxyfilePath)

	& $doxygenPath $doxyfilePath
	if ($LASTEXITCODE -ne 0) {
		throw ("Failed to run Doxygen. Exit code: {0}" -f $LASTEXITCODE)
	}

	Write-Step 'Documentation generated'
	Write-Info 'Open build/docs/html/index.html to browse the generated pages.'
}
catch {
	Write-Fail $_.Exception.Message
	exit 1
}
