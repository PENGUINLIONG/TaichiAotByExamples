
if (-not (Test-Path "tmp")) {
    New-Item -ItemType Directory "tmp"
}

Push-Location "tmp"
$SiteRepoName = "taichi-aot-by-examples.github.io"
if (Test-Path $SiteRepoName) {
    Remove-Item $SiteRepoName -Recurse -Force
}
New-Item -ItemType Directory $SiteRepoName

Push-Location $SiteRepoName

& git init
& git remote add origin "https://github.com/PENGUINLIONG/$SiteRepoName"
Copy-Item "../../mdbook/book/*" -Recurse
& git add .
& git commit -m "Publish to Github Pages"
& git push --force --set-upstream origin master

Pop-Location # $SiteRepoName

Pop-Location # tmp
