param(
    [string] $UserName,
    [string] $SiteRepoName
)

if (-not (Test-Path "tmp")) {
    New-Item -ItemType Directory "tmp"
}

if (-not $UserName) {
    $UserName = & git config --get user.name
    $UserName = $UserName.Trim()
}
if (-not $SiteRepoName) {
    $SiteRepoName = "taichi-aot-by-examples.github.io"
}

$RepoUrl = "https://github.com/$UserName/$SiteRepoName"

Push-Location "tmp"

if (Test-Path $SiteRepoName) {
    Remove-Item $SiteRepoName -Recurse -Force
}
New-Item -ItemType Directory $SiteRepoName

Push-Location $SiteRepoName

& git init
& git remote add origin "$RepoUrl"
Copy-Item "../../mdbook/book/*" -Recurse
Copy-Item "../../mdbook/README.md"
Copy-Item "../../LICENSE*"
& git add .
& git commit -m "Publish to Github Pages"
& git branch -m "master"
& git push --force --set-upstream origin master

Pop-Location # $SiteRepoName

Pop-Location # tmp
