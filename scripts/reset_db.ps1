$ErrorActionPreference = 'Stop'

$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectRoot = Split-Path -Parent $scriptDirectory
$databasePath = Join-Path $projectRoot 'database\app.db'

if (Test-Path $databasePath) {
	Remove-Item $databasePath -Force
	Write-Host 'Database removed successfully.'
}
else {
	Write-Host 'No existing database file was found.'
}

Write-Host 'The schema will be recreated automatically on the next run.'
