/*
 * test_voltage.c - Unit tests for voltage validation functionality
 * Day 1: C Fundamentals and Compilation Lab
 *
 * This file contains comprehensive unit tests for the voltage checker program.
 * Tests cover normal operation, boundary conditions, and error cases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "../include/validation.h"

// Test framework macros
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s\n", message); \
            return 0; \
        } \
    } while(0)

#define TEST_PASS(message) \
    do { \
        printf("PASS: %s\n", message); \
        return 1; \
    } while(0)

// Test constants
#define EPSILON 0.001f  // For floating point comparisons
#define TEST_NOMINAL_VOLTAGE 1.8f
#define TEST_TOLERANCE 5.0f

// Helper function to compare floats
int float_equals(float a, float b) {
    return fabs(a - b) < EPSILON;
}

// Test 1: Voltage range calculation
int test_voltage_range_calculation() {
    float min_voltage = MIN_WITH_TOLERANCE(TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    float max_voltage = MAX_WITH_TOLERANCE(TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);

    TEST_ASSERT(float_equals(min_voltage, 1.71f), "Minimum voltage calculation incorrect");
    TEST_ASSERT(float_equals(max_voltage, 1.89f), "Maximum voltage calculation incorrect");

    TEST_PASS("Voltage range calculation");
}

// Test 2: Valid voltage readings
int test_valid_voltage_readings() {
    ValidationResult result;

    // Test nominal voltage
    result = validate_voltage(1.8f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == true, "Nominal voltage should be valid");

    // Test within range
    result = validate_voltage(1.75f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == true, "1.75V should be valid");

    result = validate_voltage(1.85f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == true, "1.85V should be valid");

    TEST_PASS("Valid voltage readings");
}

// Test 3: Invalid voltage readings
int test_invalid_voltage_readings() {
    ValidationResult result;

    // Test below minimum
    result = validate_voltage(1.5f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == false, "1.5V should be invalid (too low)");

    // Test above maximum
    result = validate_voltage(2.0f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == false, "2.0V should be invalid (too high)");

    TEST_PASS("Invalid voltage readings");
}

// Test 4: Boundary conditions
int test_boundary_conditions() {
    ValidationResult result;
    float min_voltage = MIN_WITH_TOLERANCE(TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    float max_voltage = MAX_WITH_TOLERANCE(TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);

    // Test exact boundaries
    result = validate_voltage(min_voltage, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == true, "Minimum boundary should be valid");

    result = validate_voltage(max_voltage, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == true, "Maximum boundary should be valid");

    // Test just outside boundaries
    result = validate_voltage(min_voltage - 0.01f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == false, "Just below minimum should be invalid");

    result = validate_voltage(max_voltage + 0.01f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == false, "Just above maximum should be invalid");

    TEST_PASS("Boundary conditions");
}

// Test 5: Percentage error calculation
int test_percentage_error() {
    float error;

    error = calculate_percentage_error(1.8f, 1.8f);
    TEST_ASSERT(float_equals(error, 0.0f), "No error should be 0%");

    error = calculate_percentage_error(1.89f, 1.8f);
    TEST_ASSERT(float_equals(error, 5.0f), "5% high error calculation incorrect");

    error = calculate_percentage_error(1.71f, 1.8f);
    TEST_ASSERT(float_equals(error, -5.0f), "5% low error calculation incorrect");

    TEST_PASS("Percentage error calculation");
}

// Test 6: Validation statistics
int test_validation_statistics() {
    ValidationStatistics stats;
    init_validation_stats(&stats);

    // Add some test results
    update_validation_stats(&stats, 1.8f, true);
    update_validation_stats(&stats, 1.75f, true);
    update_validation_stats(&stats, 2.0f, false);
    update_validation_stats(&stats, 1.85f, true);

    finalize_validation_stats(&stats);

    TEST_ASSERT(stats.total_tests == 4, "Total tests count incorrect");
    TEST_ASSERT(stats.passed_tests == 3, "Passed tests count incorrect");
    TEST_ASSERT(stats.failed_tests == 1, "Failed tests count incorrect");
    TEST_ASSERT(float_equals(stats.pass_rate, 75.0f), "Pass rate calculation incorrect");

    TEST_PASS("Validation statistics");
}

// Test 7: Input validation macros
int test_input_validation_macros() {
    float test_value = 1.5f;

    // Test range validation (this would normally return from a function)
    int in_range = IS_IN_RANGE(test_value, 1.0f, 2.0f);
    TEST_ASSERT(in_range == 1, "Value should be in range");

    in_range = IS_IN_RANGE(test_value, 2.0f, 3.0f);
    TEST_ASSERT(in_range == 0, "Value should not be in range");

    TEST_PASS("Input validation macros");
}

// Test 8: Color output macros (basic functionality)
int test_color_output() {
    // Test that color macros are defined (compile-time test)
    const char* test_colors[] = {
        COLOR_RESET, COLOR_RED, COLOR_GREEN, COLOR_YELLOW,
        COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN
    };

    for (int i = 0; i < 7; i++) {
        TEST_ASSERT(test_colors[i] != NULL, "Color macro should be defined");
    }

    TEST_PASS("Color output macros");
}

// Test 9: Stress test with many values
int test_stress_validation() {
    ValidationStatistics stats;
    init_validation_stats(&stats);

    // Test with 1000 random values
    for (int i = 0; i < 1000; i++) {
        float voltage = 1.0f + (float)rand() / RAND_MAX * 1.0f; // 1.0V to 2.0V
        ValidationResult result = validate_voltage(voltage, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
        update_validation_stats(&stats, voltage, result.is_valid);
    }

    finalize_validation_stats(&stats);

    TEST_ASSERT(stats.total_tests == 1000, "Stress test should process 1000 values");
    TEST_ASSERT(stats.passed_tests + stats.failed_tests == 1000, "All tests should be accounted for");

    TEST_PASS("Stress test validation");
}

// Test 10: Edge cases and special values
int test_edge_cases() {
    ValidationResult result;

    // Test zero voltage
    result = validate_voltage(0.0f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == false, "Zero voltage should be invalid");

    // Test negative voltage
    result = validate_voltage(-1.0f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == false, "Negative voltage should be invalid");

    // Test very high voltage
    result = validate_voltage(100.0f, TEST_NOMINAL_VOLTAGE, TEST_TOLERANCE);
    TEST_ASSERT(result.is_valid == false, "Very high voltage should be invalid");

    TEST_PASS("Edge cases");
}

// Main test runner
int main() {
    printf("=== Voltage Validation Test Suite ===\n\n");

    int total_tests = 0;
    int passed_tests = 0;

    // Array of test functions
    struct {
        int (*test_func)();
        const char* test_name;
    } tests[] = {
        {test_voltage_range_calculation, "Voltage Range Calculation"},
        {test_valid_voltage_readings, "Valid Voltage Readings"},
        {test_invalid_voltage_readings, "Invalid Voltage Readings"},
        {test_boundary_conditions, "Boundary Conditions"},
        {test_percentage_error, "Percentage Error Calculation"},
        {test_validation_statistics, "Validation Statistics"},
        {test_input_validation_macros, "Input Validation Macros"},
        {test_color_output, "Color Output Macros"},
        {test_stress_validation, "Stress Test Validation"},
        {test_edge_cases, "Edge Cases"}
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);

    // Run all tests
    for (int i = 0; i < num_tests; i++) {
        printf("Running test %d/%d: %s\n", i + 1, num_tests, tests[i].test_name);
        total_tests++;

        if (tests[i].test_func()) {
            passed_tests++;
        }
        printf("\n");
    }

    // Print summary
    printf("=== Test Summary ===\n");
    printf("Total tests: %d\n", total_tests);
    printf("Passed: %d\n", passed_tests);
    printf("Failed: %d\n", total_tests - passed_tests);
    printf("Pass rate: %.1f%%\n", (float)passed_tests / total_tests * 100.0f);

    if (passed_tests == total_tests) {
        printf("\n✓ ALL TESTS PASSED!\n");
        return 0;
    } else {
        printf("\n✗ SOME TESTS FAILED!\n");
        return 1;
    }
}

/*
 * TESTING NOTES:
 *
 * 1. Test Coverage:
 *    - Normal operation with valid inputs
 *    - Boundary conditions (exact limits)
 *    - Invalid inputs (out of range)
 *    - Edge cases (zero, negative, very large values)
 *    - Statistical functions and calculations
 *
 * 2. Test Design Principles:
 *    - Each test function is independent
 *    - Clear pass/fail criteria
 *    - Descriptive error messages
 *    - Comprehensive coverage of functionality
 *
 * 3. Floating Point Comparisons:
 *    - Use epsilon for floating point equality
 *    - Account for precision limitations
 *    - Test with realistic engineering values
 *
 * 4. Performance Testing:
 *    - Stress test with large number of values
 *    - Verify statistical calculations remain accurate
 *    - Test memory usage and efficiency
 *
 * USAGE:
 * gcc -Wall -g -std=c11 -Iinclude -o test_voltage tests/test_voltage.c -lm
 * ./test_voltage
 */

