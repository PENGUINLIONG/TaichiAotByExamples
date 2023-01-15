param(
    [string] $BuildDir = "build-test",
    [switch] $UpdateLogs
)

if (-not (Test-Path $BuildDir)) {
    New-Item -ItemType Directory $BuildDir
}

Push-Location $BuildDir
& cmake ..
if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configuration failed"
}

& cmake --build .
if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake build failed"
}
Pop-Location

Get-ChildItem $BuildDir | ForEach-Object {
    $BaseDir = "$_"
    if (-not (Test-Path $BaseDir -PathType Container)) {
        return;
    }

    $FileName = Split-Path $BaseDir -Leaf
    $ExecutablePath = Join-Path $BaseDir "$FileName"
    if (-not (Test-Path $ExecutablePath -PathType Leaf)) {
        return;
    }

    $RefLogPath = "tests/refs/$FileName.log"
    $LogPath = Join-Path $BaseDir "$FileName.log"

    if ($UpdateLogs) {
        Copy-Item $LogPath $RefLogPath
    } else {
        $Expect = Get-Content $RefLogPath -Raw
        $Actual = Get-Content $LogPath -Raw
        $Diff = Compare-Object $Expect $Actual -CaseSensitive
        if ($Diff) {
            $MismatchMessage = @"
Example output log mismatched
Expect:
------
$Expect
------
Actual:
------
$Actual
------
"@
            Write-Error $MismatchMessage
        }
    }

    if (Test-Path $ExecutablePath) {
        Write-Host "Run $ExecutablePath"
        & $ExecutablePath > $LogPath
    }
}
