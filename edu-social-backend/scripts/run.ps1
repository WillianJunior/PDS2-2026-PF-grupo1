$ErrorActionPreference = 'Stop'

$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectRoot = Split-Path -Parent $scriptDirectory
$binaryPath = Join-Path $projectRoot 'build\bin\edu_social_backend.exe'

Set-Location $projectRoot

if (-not (Test-Path $binaryPath)) {
	throw 'Binary was not found. Run scripts/setup.ps1 first.'
}

Write-Host 'Iniciando servidor em http://localhost:18080 ...'
& $binaryPath
