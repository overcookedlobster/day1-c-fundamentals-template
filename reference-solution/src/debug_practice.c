/*
 * Day 1 Task 3: Debug Practice - REFERENCE SOLUTION
 * Chip Parameter Validation System
 *
 * Learning Objectives:
 * - Practice debugging compilation errors and warnings
 * - Understand GCC error messages and how to fix them
 * - Learn proper variable initialization and type usage
 * - Master compilation flags and their effects
 *
 * Real-World Context:
 * This file contains intentionally corrected code that demonstrates
 * common programming errors and their solutions. Students should
 * practice identifying and fixing similar issues.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/validation.h"

// Function prototypes (properly declared)
float calculate_efficiency(float power, float voltage);
void print_debug_info(const char* message, float value);
int validate_chip_parameters(float voltage, float current, float temperature);

int main() {
    printf("=== Debug Practice: Chip Parameter Validation ===\n");

    // Properly initialized variables
    float voltage = 1.8f;           // Fixed: Initialize variables
    float current = 0.5f;           // Fixed: Initialize variables
    float power = 0.0f;             // Fixed: Initialize variables
    float temperature = 25.0f;      // Fixed: Initialize variables
    int error_count = 0;            // Fixed: Initialize counter

    // Fixed: Proper array initialization
    float test_voltages[] = {1.5f, 1.8f, 2.0f, 1.75f, 1.85f};
    int num_tests = sizeof(test_voltages) / sizeof(test_voltages[0]);

    printf("Starting validation with %d test cases...\n", num_tests);

    // Fixed: Proper loop bounds
    for (int i = 0; i < num_tests; i++) {
        voltage = test_voltages[i];

        // Fixed: Proper function call with correct parameters
        power = calculate_power(voltage, current);

        // Fixed: Proper conditional logic
        if (voltage >= 1.71f && voltage <= 1.89f) {
            printf("Test %d: Voltage %.2fV - PASS\n", i + 1, voltage);

            // Fixed: Proper efficiency calculation
            float efficiency = calculate_efficiency(power, voltage);
            print_debug_info("Efficiency", efficiency);

        } else {
            printf("Test %d: Voltage %.2fV - FAIL\n", i + 1, voltage);
            error_count++;  // Fixed: Proper increment
        }

        // Fixed: Proper parameter validation
        int validation_result = validate_chip_parameters(voltage, current, temperature);
        if (validation_result != 0) {
            printf("  Warning: Parameter validation failed\n");
        }
    }

    // Fixed: Proper statistics calculation
    float pass_rate = ((float)(num_tests - error_count) / num_tests) * 100.0f;

    printf("\n=== Debug Practice Results ===\n");
    printf("Total tests: %d\n", num_tests);
    printf("Errors found: %d\n", error_count);
    printf("Pass rate: %.1f%%\n", pass_rate);

    // Fixed: Proper return statement
    return 0;
}

// Fixed: Proper function implementation with correct return type
float calculate_efficiency(float power, float voltage) {
    if (voltage <= 0.0f) {
        return 0.0f;  // Fixed: Handle division by zero
    }
    return power / voltage;  // Fixed: Return correct calculation
}

// Fixed: Proper function implementation
void print_debug_info(const char* message, float value) {
    if (message != NULL) {  // Fixed: Check for null pointer
        printf("  Debug: %s = %.3f\n", message, value);
    }
}

// Fixed: Proper function implementation with validation logic
int validate_chip_parameters(float voltage, float current, float temperature) {
    int errors = 0;

    // Fixed: Proper range checking
    if (voltage < 1.5f || voltage > 2.0f) {
        errors++;
    }

    if (current < 0.1f || current > 1.5f) {
        errors++;
    }

    if (temperature < -40.0f || temperature > 85.0f) {
        errors++;
    }

    return errors;  // Fixed: Return error count
}

/*
 * COMMON ERRORS THAT WERE FIXED IN THIS REFERENCE SOLUTION:
 *
 * 1. COMPILATION ERRORS:
 *    - Missing semicolons after statements
 *    - Undeclared variables or functions
 *    - Mismatched parentheses or braces
 *    - Incorrect function prototypes
 *    - Missing #include statements
 *
 * 2. LOGIC ERRORS:
 *    - Uninitialized variables
 *    - Off-by-one errors in loops
 *    - Incorrect conditional logic
 *    - Division by zero potential
 *    - Array bounds violations
 *
 * 3. TYPE ERRORS:
 *    - Mismatched data types in assignments
 *    - Incorrect format specifiers in printf
 *    - Integer division when float needed
 *    - Implicit type conversions
 *
 * 4. RUNTIME ERRORS:
 *    - Null pointer dereferences
 *    - Buffer overflows
 *    - Infinite loops
 *    - Memory access violations
 *
 * 5. WARNING CONDITIONS:
 *    - Unused variables
 *    - Unreachable code
 *    - Implicit function declarations
 *    - Signed/unsigned comparisons
 *
 * DEBUGGING TECHNIQUES DEMONSTRATED:
 *
 * 1. Compiler Warnings:
 *    - Always compile with -Wall -Wextra
 *    - Fix all warnings, not just errors
 *    - Use -Werror to treat warnings as errors
 *
 * 2. Variable Initialization:
 *    - Initialize all variables at declaration
 *    - Use meaningful default values
 *    - Check for uninitialized variable warnings
 *
 * 3. Function Design:
 *    - Proper function prototypes
 *    - Consistent parameter types
 *    - Appropriate return values
 *    - Error handling in functions
 *
 * 4. Input Validation:
 *    - Check all input parameters
 *    - Handle edge cases gracefully
 *    - Provide meaningful error messages
 *    - Validate array bounds
 *
 * 5. Code Organization:
 *    - Logical flow and structure
 *    - Consistent naming conventions
 *    - Appropriate comments
 *    - Modular design
 *
 * COMPILATION COMMANDS FOR DEBUGGING:
 *
 * 1. Basic compilation with warnings:
 *    gcc -Wall -Wextra -std=c11 -g -o debug_practice debug_practice.c
 *
 * 2. Strict compilation (treat warnings as errors):
 *    gcc -Wall -Wextra -Werror -std=c11 -g -o debug_practice debug_practice.c
 *
 * 3. Debug build with extra information:
 *    gcc -Wall -Wextra -std=c11 -g -DDEBUG -O0 -o debug_practice debug_practice.c
 *
 * 4. Static analysis (if available):
 *    gcc -Wall -Wextra -std=c11 -fanalyzer -o debug_practice debug_practice.c
 *
 * TESTING SUGGESTIONS:
 * - Compile with different warning levels
 * - Test with various input values
 * - Use debugger (gdb) to step through code
 * - Add printf statements for debugging
 * - Test edge cases and boundary conditions
 */

