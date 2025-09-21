#!/bin/bash
# compilation_demo.sh - Compilation demonstration script for Day 1 C Fundamentals
# This script demonstrates different compilation modes and flags

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compilation configuration
CC="gcc"
CFLAGS="-Wall -Wextra -std=c11 -Iinclude"
DEBUG_FLAGS="-g -DDEBUG -O0"
RELEASE_FLAGS="-O2 -DNDEBUG"

# Function to print colored output
print_status() {
    local status=$1
    local message=$2
    case $status in
        "INFO")
            echo -e "${BLUE}ℹ INFO${NC}: $message"
            ;;
        "SUCCESS")
            echo -e "${GREEN}✓ SUCCESS${NC}: $message"
            ;;
        "WARNING")
            echo -e "${YELLOW}⚠ WARNING${NC}: $message"
            ;;
        "ERROR")
            echo -e "${RED}✗ ERROR${NC}: $message"
            ;;
    esac
}

# Function to demonstrate compilation flags
demonstrate_compilation_flags() {
    print_status "INFO" "Demonstrating different GCC compilation flags"

    echo "Basic compilation flags used in Day 1:"
    echo "  -Wall      : Enable all common warnings"
    echo "  -Wextra    : Enable extra warnings beyond -Wall"
    echo "  -std=c11   : Use C11 standard"
    echo "  -Iinclude  : Add include directory to search path"
    echo "  -g         : Include debugging information"
    echo "  -O0        : No optimization (for debugging)"
    echo "  -O2        : Level 2 optimization (for release)"
    echo
}

# Function to compile a program with different modes
compile_program_modes() {
    local program_name=$1
    local source_file="reference-solution/src/${program_name}.c"
    local validation_lib="src/validation_lib.c"

    if [ ! -f "$source_file" ]; then
        print_status "ERROR" "Source file $source_file not found"
        return 1
    fi

    print_status "INFO" "Demonstrating compilation modes for $program_name"

    # Debug compilation
    local debug_output="${program_name}_debug"
    if $CC $CFLAGS $DEBUG_FLAGS -o "$debug_output" "$source_file" "$validation_lib" -lm 2>/dev/null; then
        print_status "SUCCESS" "Debug compilation completed: $debug_output"
        if command -v ls >/dev/null 2>&1; then
            echo "Debug build size: $(ls -lh "$debug_output" | awk '{print $5}')"
        fi
    else
        print_status "ERROR" "Debug compilation failed"
        return 1
    fi

    # Release compilation
    local release_output="${program_name}_release"
    if $CC $CFLAGS $RELEASE_FLAGS -o "$release_output" "$source_file" "$validation_lib" -lm 2>/dev/null; then
        print_status "SUCCESS" "Release compilation completed: $release_output"
        if command -v ls >/dev/null 2>&1; then
            echo "Release build size: $(ls -lh "$release_output" | awk '{print $5}')"
        fi
    else
        print_status "ERROR" "Release compilation failed"
        return 1
    fi

    return 0
}

# Function to demonstrate compilation differences
demonstrate_compilation_differences() {
    local program_name="voltage_checker"

    print_status "INFO" "Demonstrating debug vs release compilation differences"

    # Show compilation commands
    echo "=== Compilation Commands ==="
    echo "Debug compilation:"
    echo "  gcc $CFLAGS $DEBUG_FLAGS -o ${program_name}_debug reference-solution/src/${program_name}.c src/validation_lib.c -lm"
    echo
    echo "Release compilation:"
    echo "  gcc $CFLAGS $RELEASE_FLAGS -o ${program_name}_release reference-solution/src/${program_name}.c src/validation_lib.c -lm"
    echo

    # Compile both versions
    if compile_program_modes "$program_name"; then
        echo
        echo "=== Build Comparison ==="

        local debug_binary="${program_name}_debug"
        local release_binary="${program_name}_release"

        if [ -f "$debug_binary" ] && [ -f "$release_binary" ]; then
            echo "Debug build:"
            file "$debug_binary" 2>/dev/null || echo "  File info not available"
            ls -lh "$debug_binary" 2>/dev/null | awk '{print "  Size: " $5}' || echo "  Size info not available"

            echo
            echo "Release build:"
            file "$release_binary" 2>/dev/null || echo "  File info not available"
            ls -lh "$release_binary" 2>/dev/null | awk '{print "  Size: " $5}' || echo "  Size info not available"

            echo
            echo "Key differences:"
            echo "  - Debug: Includes debugging symbols, no optimization"
            echo "  - Release: Optimized for performance, smaller size"
            echo "  - Debug: Better for development and debugging"
            echo "  - Release: Better for production deployment"
        fi
    fi
}

# Function to show usage
show_usage() {
    echo "Usage: $0 [program_name|demo|help]"
    echo
    echo "Arguments:"
    echo "  program_name  Compile specific program with different modes (e.g., voltage_checker)"
    echo "  demo          Demonstrate compilation differences (debug vs release)"
    echo "  help          Show this help message"
    echo
    echo "Examples:"
    echo "  $0 voltage_checker    # Compile voltage checker in debug and release modes"
    echo "  $0 demo              # Show compilation differences"
    echo "  $0 help              # Show this help"
}

# Main script logic
main() {
    echo "=== Compilation Demonstration Script ==="
    echo "Day 1: C Fundamentals and Compilation Lab"
    echo

    case "${1:-demo}" in
        "help"|"-h"|"--help")
            show_usage
            ;;
        "demo")
            demonstrate_compilation_flags
            demonstrate_compilation_differences
            ;;
        "voltage_checker"|"power_calculator"|"debug_practice"|"safety_validator"|"multi_validator"|"batch_processor")
            demonstrate_compilation_flags
            compile_program_modes "$1"
            ;;
        *)
            print_status "ERROR" "Unknown argument: $1"
            show_usage
            exit 1
            ;;
    esac
}

# Run main function with all arguments
main "$@"

