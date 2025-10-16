#!/bin/bash

# Build script for CMake project
# Compatible with Linux, macOS, and Windows (via Git Bash/WSL)
# Usage: ./build.sh [Debug|Release]

# Set default build type to Release if no argument provided
BUILD_TYPE=${1:-Release}

# Validate build type
if [[ "$BUILD_TYPE" != "Debug" && "$BUILD_TYPE" != "Release" ]]; then
    echo "Error: Build type must be 'Debug' or 'Release'"
    echo "Usage: $0 [Debug|Release]"
    exit 1
fi

# Convert build type to lowercase for directory name
BUILD_DIR_SUFFIX=$(echo "$BUILD_TYPE" | tr '[:upper:]' '[:lower:]')
BUILD_DIR="build/$BUILD_DIR_SUFFIX"

# Colors for output (if terminal supports it)
if [[ -t 1 ]]; then
    RED='\033[0;31m'
    GREEN='\033[0;32m'
    YELLOW='\033[1;33m'
    BLUE='\033[0;34m'
    NC='\033[0m' # No Color
else
    RED=''
    GREEN=''
    YELLOW=''
    BLUE=''
    NC=''
fi

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Check if CMake is available
if ! command -v cmake &> /dev/null; then
    print_error "CMake is not installed or not in PATH"
    exit 1
fi

# Check if CMakeLists.txt exists
if [[ ! -f "CMakeLists.txt" ]]; then
    print_error "CMakeLists.txt not found in current directory"
    exit 1
fi

print_status "Building project in $BUILD_TYPE mode"
print_status "Build directory: $BUILD_DIR"

# Create build directory if it doesn't exist
if [[ ! -d "$BUILD_DIR" ]]; then
    print_status "Creating build directory: $BUILD_DIR"
    mkdir -p "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR" || {
    print_error "Failed to enter build directory: $BUILD_DIR"
    exit 1
}

# Configure with CMake
print_status "Configuring CMake..."
if cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ../..; then
    print_success "CMake configuration completed"
else
    print_error "CMake configuration failed"
    exit 1
fi

# Build the project
print_status "Building project..."
if cmake --build . --config "$BUILD_TYPE"; then
    print_success "Build completed successfully"

    # Show build information
    echo ""
    print_status "Build Information:"
    echo "  - Build Type: $BUILD_TYPE"
    echo "  - Build Directory: $BUILD_DIR"
    echo "  - Executable: $(find . -name "aes256*" -type f -executable 2>/dev/null | head -1 || echo "aes256")"
else
    print_error "Build failed"
    exit 1
fi

# Optional: Run tests if they exist
if [[ -f "CTestTestfile.cmake" ]] || find . -name "*test*" -type f -executable &>/dev/null; then
    echo ""
    read -p "Run tests? (y/N): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        print_status "Running tests..."
        if cmake --build . --target test 2>/dev/null || ctest 2>/dev/null; then
            print_success "Tests completed"
        else
            print_warning "No tests found or tests failed"
        fi
    fi
fi

print_success "Script completed successfully"
