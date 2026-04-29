$ErrorActionPreference = 'Stop'

$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectRoot = Split-Path -Parent $scriptDirectory
$databasePath = Join-Path $projectRoot 'database\app.db'

if (Test-Path $databasePath) {
	Remove-Item $databasePath -Force
	Write-Host 'Banco removido com sucesso.'
}
else {
	Write-Host 'Nenhum banco existente para remover.'
}

Write-Host 'O schema sera recriado automaticamente na proxima execucao.'
