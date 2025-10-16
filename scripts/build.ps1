#!/usr/bin/env pwsh
<#
.SYNOPSIS
  Cross-platform CMake build script (Linux, macOS, Windows via PowerShell 5.1+ / 7+)

.DESCRIPTION
  Configures and builds the project described by CMakeLists.txt into:
    - build/debug for Debug
    - build/release for Release
  Usage: ./build.ps1 [Debug|Release]
  Default build type: Release
#>

param(
    [ValidateSet('Debug','Release')]
    [string]$BuildType = 'Release'
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Write-Info   { param([string]$m) Write-Host "[INFO] $m"  -ForegroundColor Cyan   }
function Write-Ok     { param([string]$m) Write-Host "[OK]   $m"  -ForegroundColor Green  }
function Write-Warn   { param([string]$m) Write-Host "[WARN] $m"  -ForegroundColor Yellow }
function Write-Fail   { param([string]$m) Write-Host "[FAIL] $m"  -ForegroundColor Red    }

# Normalize OS flags for both Windows PowerShell 5.1 and PowerShell 7+
# If the automatic variables are missing, define them from .NET PlatformID
if ($null -eq (Get-Variable -Name IsWindows -Scope Script -ErrorAction SilentlyContinue)) {
    $plat = [System.Environment]::OSVersion.Platform
    $script:IsWindows = ($plat -eq [System.PlatformID]::Win32NT)
    $script:IsLinux   = ($plat -eq [System.PlatformID]::Unix -and $PSVersionTable.Platform -eq 'Unix')
    $script:IsMacOS   = ($plat -eq [System.PlatformID]::Unix -and $PSVersionTable.Platform -eq 'Unix' -and ($PSVersionTable.OS -match 'Darwin|Mac'))
}

# Ensure cmake exists
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Fail "CMake not found in PATH. Install CMake and retry."
    exit 1
}

# Ensure CMakeLists.txt exists in current directory
$cmakeLists = Join-Path (Get-Location) 'CMakeLists.txt'
if (-not (Test-Path $cmakeLists)) {
    Write-Fail "CMakeLists.txt not found in current directory."
    exit 1
}

# Build directory under ./build/{debug|release}
$dirSuffix = $BuildType.ToLowerInvariant()
$buildDir  = Join-Path 'build' $dirSuffix
Write-Info "Build type: $BuildType"
Write-Info "Build dir : $buildDir"

if (-not (Test-Path $buildDir)) {
    Write-Info "Creating build directory: $buildDir"
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

Push-Location $buildDir
try {
    # Compute project root (two levels up from build/{debug|release})
    $projRootCandidate = Join-Path (Get-Location) ".."
    $projRootCandidate = Join-Path $projRootCandidate ".."
    $projRoot = (Resolve-Path $projRootCandidate).Path

    # Configure cmake
    $cmakeArgs = @(
        '-S', $projRoot,
        '-B', '.',
        "-DCMAKE_BUILD_TYPE=$BuildType"
    )

    # Prefer Ninja on Windows if available
    if ($IsWindows -and (Get-Command ninja -ErrorAction SilentlyContinue)) {
        $cmakeArgs += @('-G','Ninja')
    }

    Write-Info "Configuring CMake..."
    cmake @cmakeArgs
    Write-Ok "Configuration completed."

    Write-Info "Building..."
    cmake --build . --config $BuildType
    Write-Ok "Build completed."

    # Locate executable
    Write-Info "Searching for output executable..."
    $execNames = @('aes256','aes256.exe')
    $exec = Get-ChildItem -Recurse -File |
            Where-Object {
                ($execNames -contains $_.Name) -or
                        (($_.Name -like 'aes256*') -and ($_.Extension -eq '' -or $_.Extension -eq '.exe'))
            } |
            Select-Object -First 1

    if ($null -ne $exec) {
        Write-Ok "Executable: $($exec.FullName)"
    } else {
        Write-Warn "Executable not found automatically. Check build outputs for target 'aes256'."
    }
}
catch {
    Write-Fail $_.Exception.Message
    exit 1
}
finally {
    Pop-Location
}
