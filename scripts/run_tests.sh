#!/bin/bash
# run_tests.sh - Automated test runner for Day 1 C Fundamentals
# Day 1: C Fundamentals and Compilation Lab
#
# This script runs comprehensive tests for all Day 1 programs and validates
# the implementation against expected outputs and specifications.

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test configuration
TEST_DIR="tests"
BUILD_DIR="build"
EXPECTED_DIR="tests/expected_outputs"
RESULTS_DIR="test_results"
LOG_FILE="test_results/test_log.txt"

# Create necessary directories
mkdir -p "$RESULTS_DIR"
mkdir -p "$BUILD_DIR"

# Initialize log file
echo "=== Day 1 C Fundamentals Test Run ===" > "$LOG_FILE"
echo "Date: $(date)" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"

# Function to print colored output
print_status() {
    local status=$1
    local message=$2
    case $status in
        "PASS")
            echo -e "${GREEN}✓ PASS${NC}: $message"
            echo "PASS: $message" >> "$LOG_FILE"
            ;;
        "FAIL")
            echo -e "${RED}✗ FAIL${NC}: $message"
            echo "FAIL: $message" >> "$LOG_FILE"
            ;;
        "INFO")
            echo -e "${BLUE}ℹ INFO${NC}: $message"
            echo "INFO: $message" >> "$LOG_FILE"
            ;;
        "WARN")
            echo -e "${YELLOW}⚠ WARN${NC}: $message"
            echo "WARN: $message" >> "$LOG_FILE"
            ;;
    esac
}

# Function to run a single test
run_test() {
    local test_name=$1
    local test_command=$2
    local expected_exit_code=${3:-0}

    print_status "INFO" "Running test: $test_name"

    if eval "$test_command" >> "$LOG_FILE" 2>&1; then
        local exit_code=$?
        if [ $exit_code -eq $expected_exit_code ]; then
            print_status "PASS" "$test_name"
            return 0
        else
            print_status "FAIL" "$test_name (unexpected exit code: $exit_code)"
            return 1
        fi
    else
        print_status "FAIL" "$test_name (command failed)"
        return 1
    fi
}

# Function to test compilation
test_compilation() {
    local program=$1
    local source_file=$2

    print_status "INFO" "Testing compilation of $program"

    if gcc -Wall -Wextra -std=c11 -Iinclude -g -o "$program" "$source_file" -lm 2>> "$LOG_FILE"; then
        print_status "PASS" "Compilation of $program"
        return 0
    else
        print_status "FAIL" "Compilation of $program"
        return 1
    fi
}

# Function to test program execution with input
test_program_with_input() {
    local program=$1
    local input_file=$2
    local expected_output_pattern=$3

    if [ ! -f "$program" ]; then
        print_status "FAIL" "$program not found"
        return 1
    fi

    local output_file="$RESULTS_DIR/${program}_output.txt"

    if [ -f "$input_file" ]; then
        ./"$program" < "$input_file" > "$output_file" 2>&1
    else
        echo -e "1.8\n0.5\n-1" | ./"$program" > "$output_file" 2>&1
    fi

    if grep -q "$expected_output_pattern" "$output_file"; then
        print_status "PASS" "$program execution test"
        return 0
    else
        print_status "FAIL" "$program execution test (output mismatch)"
        return 1
    fi
}

# Main test execution
main() {
    echo "=== Day 1 C Fundamentals Test Suite ==="
    echo "Starting comprehensive testing..."
    echo

    local total_tests=0
    local passed_tests=0

    # Test 1: Compilation Tests
    echo "--- Phase 1: Compilation Tests ---"

    # Test unit test compilation
    if test_compilation "test_voltage" "tests/test_voltage.c"; then
        ((passed_tests++))
    fi
    ((total_tests++))

    if test_compilation "test_power" "tests/test_power.c"; then
        ((passed_tests++))
    fi
    ((total_tests++))

    # Test main program compilation (if source files exist)
    if [ -f "src/voltage_checker.c" ]; then
        if test_compilation "voltage_checker" "src/voltage_checker.c"; then
            ((passed_tests++))
        fi
        ((total_tests++))
    fi

    if [ -f "src/power_calculator.c" ]; then
        if test_compilation "power_calculator" "src/power_calculator.c"; then
            ((passed_tests++))
        fi
        ((total_tests++))
    fi

    echo

    # Test 2: Unit Tests Execution
    echo "--- Phase 2: Unit Test Execution ---"

    if [ -f "test_voltage" ]; then
        if run_test "Voltage validation unit tests" "./test_voltage"; then
            ((passed_tests++))
        fi
        ((total_tests++))
    fi

    if [ -f "test_power" ]; then
        if run_test "Power calculation unit tests" "./test_power"; then
            ((passed_tests++))
        fi
        ((total_tests++))
    fi

    echo

    # Test 3: Integration Tests
    echo "--- Phase 3: Integration Tests ---"

    # Test voltage checker with sample inputs
    if [ -f "voltage_checker" ]; then
        if test_program_with_input "voltage_checker" "" "Voltage"; then
            ((passed_tests++))
        fi
        ((total_tests++))
    fi

    # Test power calculator with sample inputs
    if [ -f "power_calculator" ]; then
        if test_program_with_input "power_calculator" "" "Power"; then
            ((passed_tests++))
        fi
        ((total_tests++))
    fi

    echo

    # Test 4: Makefile Tests
    echo "--- Phase 4: Makefile Tests ---"

    if run_test "Makefile clean target" "make clean"; then
        ((passed_tests++))
    fi
    ((total_tests++))

    if run_test "Makefile all target" "make all"; then
        ((passed_tests++))
    fi
    ((total_tests++))

    if run_test "Makefile test target" "make test"; then
        ((passed_tests++))
    fi
    ((total_tests++))

    echo

    # Test 5: Code Quality Tests
    echo "--- Phase 5: Code Quality Tests ---"

    if run_test "Code style check" "make style-check"; then
        ((passed_tests++))
    fi
    ((total_tests++))

    # Check for common issues
    if find src/ -name "*.c" -exec grep -l "TODO" {} \; | wc -l | grep -q "0"; then
        print_status "PASS" "No TODO items remaining in source files"
        ((passed_tests++))
    else
        print_status "WARN" "TODO items found in source files (expected for templates)"
    fi
    ((total_tests++))

    echo

    # Test Summary
    echo "=== Test Summary ==="
    echo "Total tests: $total_tests"
    echo "Passed: $passed_tests"
    echo "Failed: $((total_tests - passed_tests))"

    local pass_rate=$((passed_tests * 100 / total_tests))
    echo "Pass rate: ${pass_rate}%"

    if [ $passed_tests -eq $total_tests ]; then
        print_status "PASS" "All tests completed successfully!"
        echo
        echo "✓ Your Day 1 implementation is working correctly!"
        exit 0
    else
        print_status "FAIL" "Some tests failed. Check the log for details."
        echo
        echo "✗ Please review the failed tests and fix any issues."
        echo "Log file: $LOG_FILE"
        exit 1
    fi
}

# Function to show usage
show_usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  -h, --help     Show this help message"
    echo "  -v, --verbose  Enable verbose output"
    echo "  -q, --quick    Run only essential tests"
    echo "  -c, --clean    Clean before testing"
    echo
    echo "Examples:"
    echo "  $0              # Run all tests"
    echo "  $0 --clean     # Clean and run all tests"
    echo "  $0 --quick     # Run only compilation and unit tests"
}

# Parse command line arguments
VERBOSE=false
QUICK=false
CLEAN=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_usage
            exit 0
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -q|--quick)
            QUICK=true
            shift
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        *)
            echo "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
done

# Clean if requested
if [ "$CLEAN" = true ]; then
    print_status "INFO" "Cleaning previous build artifacts..."
    make clean >> "$LOG_FILE" 2>&1 || true
fi

# Run main test function
main

# End of script

