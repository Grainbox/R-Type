# setup.ps1 - R-Type Windows Setup Script

$VCPKG_DIR = ".\vcpkg"

# Fix for CMake 4.0+ compatibility with older ports
$env:CMAKE_POLICY_VERSION_MINIMUM = "3.5"

# 1. Initialize Git Submodules (vcpkg)
Write-Host "--- Initializing Git Submodules ---" -ForegroundColor Cyan
if (-not (Test-Path "$VCPKG_DIR\.git")) {
    git submodule init
    git submodule update
}

# 2. Bootstrap vcpkg
Write-Host "`n--- Bootstrapping vcpkg ---" -ForegroundColor Cyan
if (-not (Test-Path "$VCPKG_DIR\vcpkg.exe")) {
    Push-Location $VCPKG_DIR
    .\bootstrap-vcpkg.bat
    Pop-Location
}

# 3. Install Dependencies
$libraries = @("asio", "raylib", "boost-serialization")
Write-Host "`n--- Installing Dependencies ---" -ForegroundColor Cyan
foreach ($lib in $libraries) {
    Write-Host "Checking $lib..."
    & "$VCPKG_DIR\vcpkg.exe" install "$lib`:x64-windows"
}

# 4. Configure CMake
Write-Host "`n--- Configuring project with CMake ---" -ForegroundColor Cyan
if (Test-Path "build\CMakeCache.txt") {
    Write-Host "Removing old CMake cache..."
    Remove-Item -Path "build\CMakeCache.txt" -Force
}
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Force -Path "build"
}

# Explicitly use Visual Studio 17 2022 generator for Windows
cmake -G "Visual Studio 17 2022" -A x64 -B build -S . `
    "-DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake" `
    "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"

if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake configuration failed!" -ForegroundColor Red
    exit 1
}

# 5. Build Project
Write-Host "`n--- Building project ---" -ForegroundColor Cyan
cmake --build build --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}

# 6. Copy Assets to root for convenience
Write-Host "`n--- Copying Assets ---" -ForegroundColor Cyan
if (Test-Path "engine\assets") {
    Copy-Item -Path "engine\assets" -Destination "assets" -Recurse -Force
}

Write-Host "`nSetup and Build Complete!" -ForegroundColor Green
Write-Host "You can find the executables in:"
Write-Host "  Server: build\server\Release\r-type_server.exe"
Write-Host "  Client: build\client\Release\r-type_client.exe"
