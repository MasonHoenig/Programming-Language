$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

$vs = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -property installationPath
& "$vs\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64 -SkipAutomaticLocation

clang++ -std=c++17 -Wall `
    -I "Driver" -I "Lexer" -I "Parser" -I "Intermediate Representation" `
    main.cpp `
    "Driver\Driver.cpp" `
    "Lexer\Lexer.cpp" `
    "Parser\Parser.cpp" `
    "Intermediate Representation\CodeGeneration.cpp" `
    -o compiler.exe

if ($LASTEXITCODE -ne 0) { Write-Host "Build failed" -ForegroundColor Red; exit 1 }
Write-Host "Build succeeded: compiler.exe" -ForegroundColor Green

.\compiler.exe testInput.swi
exit $LASTEXITCODE