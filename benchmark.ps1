$versions = @(1, 2, 3)
$sizes = @(10, 100, 500, 1000, 10000, 50000, 100000, 250000, 500000, 750000, 1000000, 1500000, 2000000)

if (Test-Path "results.csv") {
    Remove-Item "results.csv"
}

foreach ($version in $versions) {
    foreach ($size in $sizes) {
        Write-Host "Benchmarking v${version} with size $size"

        1..3 | ForEach-Object {
            .\Benchmarking.exe $version $size
        }

        1..10 | ForEach-Object {
            .\Benchmarking.exe $version $size
        }
    }
}

Write-Host "Benchmarking complete! Results saved to results.csv"