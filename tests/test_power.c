/*
 * test_power.c - Unit tests for power calculation functionality
 * Day 1: C Fundamentals and Compilation Lab
 *
 * This file contains comprehensive unit tests for the power calculator program.
 * Tests cover power calculations, input validation, and efficiency analysis.
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
#define EPSILON 0.001f
#define TEST_MAX_POWER 2.0f
#define TEST_MIN_VOLTAGE 1.5f
#define TEST_MAX_VOLTAGE 2.0f
#define TEST_MIN_CURRENT 0.1f
#define TEST_MAX_CURRENT 1.5f

// Helper function for float comparison
int float_equals(float a, float b) {
    return fabs(a - b) < EPSILON;
}

// Test 1: Basic power calculation (P = V × I)
int test_basic_power_calculation() {
    float power;

    // Test standard calculation
    power = calculate_power(1.8f, 0.5f);
    TEST_ASSERT(float_equals(power, 0.9f), "1.8V × 0.5A should equal 0.9W");

    // Test with different values
    power = calculate_power(3.3f, 0.3f);
    TEST_ASSERT(float_equals(power, 0.99f), "3.3V × 0.3A should equal 0.99W");

    // Test with integer-like values
    power = calculate_power(2.0f, 1.0f);
    TEST_ASSERT(float_equals(power, 2.0f), "2.0V × 1.0A should equal 2.0W");

    TEST_PASS("Basic power calculation");
}

// Test 2: Edge cases for power calculation
int test_power_calculation_edge_cases() {
    float power;

    // Test zero voltage
    power = calculate_power(0.0f, 0.5f);
    TEST_ASSERT(float_equals(power, 0.0f), "Zero voltage should give zero power");

    // Test zero current
    power = calculate_power(1.8f, 0.0f);
    TEST_ASSERT(float_equals(power, 0.0f), "Zero current should give zero power");

    // Test both zero
    power = calculate_power(0.0f, 0.0f);
    TEST_ASSERT(float_equals(power, 0.0f), "Zero voltage and current should give zero power");

    // Test very small values
    power = calculate_power(0.001f, 0.001f);
    TEST_ASSERT(power >= 0.0f, "Very small values should give positive power");

    TEST_PASS("Power calculation edge cases");
}

// Test 3: Power acceptability checking
int test_power_acceptability() {
    // Test power within limits
    TEST_ASSERT(is_power_acceptable(1.0f, TEST_MAX_POWER) == true, "1.0W should be acceptable (limit 2.0W)");
    TEST_ASSERT(is_power_acceptable(1.5f, TEST_MAX_POWER) == true, "1.5W should be acceptable (limit 2.0W)");
    TEST_ASSERT(is_power_acceptable(2.0f, TEST_MAX_POWER) == true, "2.0W should be acceptable (at limit)");

    // Test power over limits
    TEST_ASSERT(is_power_acceptable(2.1f, TEST_MAX_POWER) == false, "2.1W should not be acceptable (over 2.0W limit)");
    TEST_ASSERT(is_power_acceptable(3.0f, TEST_MAX_POWER) == false, "3.0W should not be acceptable (over 2.0W limit)");

    // Test boundary conditions
    TEST_ASSERT(is_power_acceptable(1.999f, TEST_MAX_POWER) == true, "Just under limit should be acceptable");
    TEST_ASSERT(is_power_acceptable(2.001f, TEST_MAX_POWER) == false, "Just over limit should not be acceptable");

    TEST_PASS("Power acceptability checking");
}

// Test 4: Power efficiency categorization
int test_power_efficiency_categories() {
    float efficient_threshold = 1.0f;
    float moderate_threshold = 1.5f;

    // Test efficient power levels
    TEST_ASSERT(0.5f <= efficient_threshold, "0.5W should be in efficient category");
    TEST_ASSERT(0.8f <= efficient_threshold, "0.8W should be in efficient category");
    TEST_ASSERT(1.0f <= efficient_threshold, "1.0W should be at efficient boundary");

    // Test moderate power levels
    TEST_ASSERT(1.2f > efficient_threshold && 1.2f <= moderate_threshold, "1.2W should be in moderate category");
    TEST_ASSERT(1.4f > efficient_threshold && 1.4f <= moderate_threshold, "1.4W should be in moderate category");

    // Test high power levels
    TEST_ASSERT(1.8f > moderate_threshold, "1.8W should be in high power category");
    TEST_ASSERT(2.0f > moderate_threshold, "2.0W should be in high power category");

    TEST_PASS("Power efficiency categorization");
}

// Test 5: Input validation ranges
int test_input_validation_ranges() {
    // Test voltage range validation
    TEST_ASSERT(IS_IN_RANGE(1.8f, TEST_MIN_VOLTAGE, TEST_MAX_VOLTAGE) == true, "1.8V should be in valid range");
    TEST_ASSERT(IS_IN_RANGE(1.0f, TEST_MIN_VOLTAGE, TEST_MAX_VOLTAGE) == false, "1.0V should be below minimum");
    TEST_ASSERT(IS_IN_RANGE(2.5f, TEST_MIN_VOLTAGE, TEST_MAX_VOLTAGE) == false, "2.5V should be above maximum");

    // Test current range validation
    TEST_ASSERT(IS_IN_RANGE(0.5f, TEST_MIN_CURRENT, TEST_MAX_CURRENT) == true, "0.5A should be in valid range");
    TEST_ASSERT(IS_IN_RANGE(0.05f, TEST_MIN_CURRENT, TEST_MAX_CURRENT) == false, "0.05A should be below minimum");
    TEST_ASSERT(IS_IN_RANGE(2.0f, TEST_MIN_CURRENT, TEST_MAX_CURRENT) == false, "2.0A should be above maximum");

    TEST_PASS("Input validation ranges");
}

// Test 6: Power density calculation
int test_power_density_calculation() {
    float power_density;

    // Test normal power density
    power_density = 0.9f / 1.8f;  // 0.9W / 1.8V
    TEST_ASSERT(float_equals(power_density, 0.5f), "Power density should be 0.5 W/V");

    // Test different voltage levels
    power_density = 1.0f / 2.0f;  // 1.0W / 2.0V
    TEST_ASSERT(float_equals(power_density, 0.5f), "Power density should be 0.5 W/V");

    power_density = 1.5f / 3.0f;  // 1.5W / 3.0V
    TEST_ASSERT(float_equals(power_density, 0.5f), "Power density should be 0.5 W/V");

    // Test high power density
    power_density = 2.0f / 1.5f;  // 2.0W / 1.5V
    TEST_ASSERT(power_density > 1.0f, "High power density should be > 1.0 W/V");

    TEST_PASS("Power density calculation");
}

// Test 7: Statistical analysis for multiple calculations
int test_power_statistics() {
    ValidationStatistics stats;
    init_validation_stats(&stats);

    // Simulate multiple power calculations
    float test_powers[] = {0.9f, 1.2f, 0.8f, 1.5f, 2.1f, 1.0f, 1.8f, 0.6f};
    int num_tests = sizeof(test_powers) / sizeof(test_powers[0]);

    for (int i = 0; i < num_tests; i++) {
        bool acceptable = is_power_acceptable(test_powers[i], TEST_MAX_POWER);
        update_validation_stats(&stats, test_powers[i], acceptable);
    }

    finalize_validation_stats(&stats);

    TEST_ASSERT(stats.total_tests == num_tests, "Total tests should match input count");
    TEST_ASSERT(stats.passed_tests == 7, "7 tests should pass (power <= 2.0W)");
    TEST_ASSERT(stats.failed_tests == 1, "1 test should fail (2.1W > 2.0W)");

    // Check average calculation
    float expected_average = (0.9f + 1.2f + 0.8f + 1.5f + 2.1f + 1.0f + 1.8f + 0.6f) / 8.0f;
    TEST_ASSERT(float_equals(stats.average_value, expected_average), "Average power calculation should be correct");

    TEST_PASS("Power statistics");
}

// Test 8: Boundary power calculations
int test_boundary_power_calculations() {
    float power;

    // Test at voltage boundaries
    power = calculate_power(TEST_MIN_VOLTAGE, 1.0f);
    TEST_ASSERT(float_equals(power, TEST_MIN_VOLTAGE), "Power at min voltage should be correct");

    power = calculate_power(TEST_MAX_VOLTAGE, 1.0f);
    TEST_ASSERT(float_equals(power, TEST_MAX_VOLTAGE), "Power at max voltage should be correct");

    // Test at current boundaries
    power = calculate_power(1.0f, TEST_MIN_CURRENT);
    TEST_ASSERT(float_equals(power, TEST_MIN_CURRENT), "Power at min current should be correct");

    power = calculate_power(1.0f, TEST_MAX_CURRENT);
    TEST_ASSERT(float_equals(power, TEST_MAX_CURRENT), "Power at max current should be correct");

    // Test maximum possible power
    power = calculate_power(TEST_MAX_VOLTAGE, TEST_MAX_CURRENT);
    float max_possible = TEST_MAX_VOLTAGE * TEST_MAX_CURRENT;
    TEST_ASSERT(float_equals(power, max_possible), "Maximum possible power should be correct");

    TEST_PASS("Boundary power calculations");
}

// Test 9: Power budget utilization
int test_power_budget_utilization() {
    float utilization;

    // Test various utilization levels
    utilization = (1.0f / TEST_MAX_POWER) * 100.0f;
    TEST_ASSERT(float_equals(utilization, 50.0f), "1.0W should be 50% utilization");

    utilization = (1.5f / TEST_MAX_POWER) * 100.0f;
    TEST_ASSERT(float_equals(utilization, 75.0f), "1.5W should be 75% utilization");

    utilization = (2.0f / TEST_MAX_POWER) * 100.0f;
    TEST_ASSERT(float_equals(utilization, 100.0f), "2.0W should be 100% utilization");

    utilization = (0.5f / TEST_MAX_POWER) * 100.0f;
    TEST_ASSERT(float_equals(utilization, 25.0f), "0.5W should be 25% utilization");

    TEST_PASS("Power budget utilization");
}

// Test 10: Comprehensive power validation scenario
int test_comprehensive_power_scenario() {
    // Simulate a complete power validation scenario
    struct {
        float voltage;
        float current;
        float expected_power;
        bool should_be_acceptable;
    } test_cases[] = {
        {1.8f, 0.5f, 0.9f, true},    // Normal operation
        {1.5f, 0.8f, 1.2f, true},    // Low voltage, higher current
        {2.0f, 1.0f, 2.0f, true},    // At power limit
        {1.8f, 1.2f, 2.16f, false}, // Over power limit
        {3.3f, 0.3f, 0.99f, true},   // High voltage, low current
    };

    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_cases; i++) {
        float power = calculate_power(test_cases[i].voltage, test_cases[i].current);
        bool acceptable = is_power_acceptable(power, TEST_MAX_POWER);

        TEST_ASSERT(float_equals(power, test_cases[i].expected_power),
                   "Power calculation should match expected value");
        TEST_ASSERT(acceptable == test_cases[i].should_be_acceptable,
                   "Power acceptability should match expected result");
    }

    TEST_PASS("Comprehensive power validation scenario");
}

// Main test runner
int main() {
    printf("=== Power Calculation Test Suite ===\n\n");

    int total_tests = 0;
    int passed_tests = 0;

    // Array of test functions
    struct {
        int (*test_func)();
        const char* test_name;
    } tests[] = {
        {test_basic_power_calculation, "Basic Power Calculation"},
        {test_power_calculation_edge_cases, "Power Calculation Edge Cases"},
        {test_power_acceptability, "Power Acceptability Checking"},
        {test_power_efficiency_categories, "Power Efficiency Categories"},
        {test_input_validation_ranges, "Input Validation Ranges"},
        {test_power_density_calculation, "Power Density Calculation"},
        {test_power_statistics, "Power Statistics"},
        {test_boundary_power_calculations, "Boundary Power Calculations"},
        {test_power_budget_utilization, "Power Budget Utilization"},
        {test_comprehensive_power_scenario, "Comprehensive Power Scenario"}
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
 * POWER TESTING NOTES:
 *
 * 1. Test Coverage:
 *    - Basic power calculations (P = V × I)
 *    - Input validation and range checking
 *    - Power efficiency categorization
 *    - Statistical analysis of multiple calculations
 *    - Boundary conditions and edge cases
 *
 * 2. Engineering Context:
 *    - Realistic power limits and operating ranges
 *    - Power density calculations for efficiency analysis
 *    - Budget utilization tracking
 *    - Comprehensive validation scenarios
 *
 * 3. Test Design:
 *    - Independent test functions
 *    - Clear pass/fail criteria
 *    - Floating point comparison with epsilon
 *    - Comprehensive edge case coverage
 *
 * 4. Performance Considerations:
 *    - Tests run quickly for continuous integration
 *    - Memory efficient test data structures
 *    - Scalable for additional test cases
 *
 * USAGE:
 * gcc -Wall -g -std=c11 -Iinclude -o test_power tests/test_power.c -lm
 * ./test_power
 */

