/*
 * Day 1 Task 3: Debug Practice - TEMPLATE WITH INTENTIONAL ERRORS
 * Chip Parameter Validation System
 *
 * Learning Objectives:
 * - Practice debugging compilation errors and warnings
 * - Understand GCC error messages and how to fix them
 * - Learn proper variable initialization and type usage
 * - Master compilation flags and their effects
 *
 * Real-World Context:
 * This file contains intentional errors for students to find and fix.
 * Students should practice identifying and correcting common C programming mistakes.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/validation.h"

// TODO: Add missing function prototypes
// float calculate_efficiency(float power, float voltage);
// void print_debug_info(const char* message, float value);
// int validate_chip_parameters(float voltage, float current, float temperature);

int main() {
    printf("=== Debug Practice: Chip Parameter Validation ===\n");

    // TODO: Initialize these variables properly
    float voltage;           // ERROR: Uninitialized variable
    float current;           // ERROR: Uninitialized variable
    float power;             // ERROR: Uninitialized variable
    float temperature;       // ERROR: Uninitialized variable
    int error_count;         // ERROR: Uninitialized variable

    // TODO: Fix array initialization
    float test_voltages[] = {1.5, 1.8, 2.0, 1.75, 1.85};  // ERROR: Missing 'f' suffix
    int num_tests = sizeof(test_voltages) / sizeof(test_voltages[0]);

    printf("Starting validation with %d test cases...\n", num_tests);

    // TODO: Fix loop bounds (off-by-one error)
    for (int i = 0; i <= num_tests; i++) {  // ERROR: Should be i < num_tests
        voltage = test_voltages[i];

        // TODO: Fix function call
        power = calculate_power(voltage, current);  // ERROR: current is uninitialized

        // TODO: Fix conditional logic
        if (voltage >= 1.71 && voltage <= 1.89) {  // ERROR: Missing 'f' suffix
            printf("Test %d: Voltage %.2fV - PASS\n", i + 1, voltage);

            // TODO: Fix function call
            // float efficiency = calculate_efficiency(power, voltage);  // ERROR: Function not defined
            // print_debug_info("Efficiency", efficiency);  // ERROR: Function not defined

        } else {
            printf("Test %d: Voltage %.2fV - FAIL\n", i + 1, voltage);
            error_count++;  // ERROR: error_count is uninitialized
        }

        // TODO: Fix function call
        // int validation_result = validate_chip_parameters(voltage, current, temperature);  // ERROR: Function not defined
        // if (validation_result != 0) {
        //     printf("  Warning: Parameter validation failed\n");
        // }
    }

    // TODO: Fix statistics calculation
    float pass_rate = ((float)(num_tests - error_count) / num_tests) * 100.0;  // ERROR: Missing 'f' suffix

    printf("\n=== Debug Practice Results ===\n");
    printf("Total tests: %d\n", num_tests);
    printf("Errors found: %d\n", error_count);
    printf("Pass rate: %.1f%%\n", pass_rate);

    // TODO: Add proper return statement
    return 0;
}

// TODO: Implement missing functions
/*
float calculate_efficiency(float power, float voltage) {
    if (voltage <= 0.0f) {
        return 0.0f;
    }
    return power / voltage;
}

void print_debug_info(const char* message, float value) {
    if (message != NULL) {
        printf("  Debug: %s = %.3f\n", message, value);
    }
}

int validate_chip_parameters(float voltage, float current, float temperature) {
    int errors = 0;

    if (voltage < 1.5f || voltage > 2.0f) {
        errors++;
    }

    if (current < 0.1f || current > 1.5f) {
        errors++;
    }

    if (temperature < -40.0f || temperature > 85.0f) {
        errors++;
    }

    return errors;
}
*/

/*
 * INTENTIONAL ERRORS IN THIS FILE (FOR STUDENTS TO FIND AND FIX):
 *
 * 1. COMPILATION ERRORS:
 *    - Missing function prototypes
 *    - Uninitialized variables
 *    - Missing 'f' suffix on float literals
 *    - Off-by-one error in loop condition
 *    - Undefined function calls
 *
 * 2. LOGIC ERRORS:
 *    - Using uninitialized variables in calculations
 *    - Array bounds violation potential
 *    - Missing error checking
 *
 * 3. BEST PRACTICES VIOLATIONS:
 *    - No input validation
 *    - Missing function implementations
 *    - Inconsistent variable initialization
 *
 * DEBUGGING EXERCISE:
 * Students should:
 * 1. Compile with -Wall -Wextra to see all warnings
 * 2. Fix compilation errors one by one
 * 3. Initialize all variables properly
 * 4. Implement missing functions
 * 5. Test with various inputs
 * 6. Verify the program runs without errors
 *
 * COMPILATION COMMAND:
 * gcc -Wall -Wextra -std=c11 -g -Iinclude -o debug_practice src/debug_practice.c
 */

