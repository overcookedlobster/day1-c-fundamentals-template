/*
 * Day 1 Task 1: Voltage Checker - REFERENCE SOLUTION
 * Chip Parameter Validation System
 *
 * Learning Objectives:
 * - Use appropriate C data types for validation (float, int, char)
 * - Implement variable declarations and basic operators
 * - Practice input validation and range checking
 * - Handle user input with scanf and provide formatted output with printf
 *
 * Real-World Context:
 * Post-silicon validation engineers must verify that chip voltages operate
 * within specified tolerances. This program simulates voltage validation
 * for a 1.8V power rail with ±5% tolerance (1.71V - 1.89V).
 */

#include <stdio.h>
#include <stdbool.h>
#include "../include/validation.h"

// Define voltage specification constants
#define NOMINAL_VOLTAGE     1.8f
#define TOLERANCE_PERCENT   5.0f
#define MIN_VOLTAGE         (NOMINAL_VOLTAGE * (1.0f - TOLERANCE_PERCENT / 100.0f))
#define MAX_VOLTAGE         (NOMINAL_VOLTAGE * (1.0f + TOLERANCE_PERCENT / 100.0f))

int main() {
    // Declare variables with appropriate data types
    float voltage_reading;      // for precise voltage measurements
    int test_count = 0;         // for counting number of tests
    int pass_count = 0;         // for counting passed tests
    char status;                // for storing pass/fail status ('P' or 'F')

    printf("=== Chip Voltage Validation System ===\n");
    printf("Nominal Voltage: %.2fV (±%.1f%%)\n", NOMINAL_VOLTAGE, TOLERANCE_PERCENT);
    printf("Acceptable Range: %.2fV - %.2fV\n\n", MIN_VOLTAGE, MAX_VOLTAGE);

    // Implement input loop for multiple voltage readings
    printf("Enter voltage readings (enter -1 to quit):\n");

    while (1) {
        printf("Voltage reading: ");

        // Get voltage input from user
        if (scanf("%f", &voltage_reading) != 1) {
            printf("Error: Invalid input. Please enter a numeric value.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        // Check for exit condition
        if (voltage_reading == -1.0f) {
            break;
        }

        // Validate input range and update counters
        test_count++;

        // Check if voltage is within acceptable range
        if (voltage_reading >= MIN_VOLTAGE && voltage_reading <= MAX_VOLTAGE) {
            status = 'P';  // Set status to 'P' for pass
            pass_count++;  // Increment pass count
            printf("✓ PASS: Voltage %.2fV is within acceptable range\n", voltage_reading);
        } else {
            status = 'F';  // Set status to 'F' for fail
            printf("✗ FAIL: Voltage %.2fV is outside acceptable range\n", voltage_reading);

            // Provide specific feedback about the failure
            if (voltage_reading < MIN_VOLTAGE) {
                printf("  → Voltage is %.2fV below minimum (%.2fV)\n",
                       MIN_VOLTAGE - voltage_reading, MIN_VOLTAGE);
            } else if (voltage_reading > MAX_VOLTAGE) {
                printf("  → Voltage is %.2fV above maximum (%.2fV)\n",
                       voltage_reading - MAX_VOLTAGE, MAX_VOLTAGE);
            }
        }
        printf("\n");
    }

    // Display final statistics
    if (test_count > 0) {
        float pass_percentage = ((float)pass_count / test_count) * 100.0f;

        printf("=== Validation Summary ===\n");
        printf("Total tests: %d\n", test_count);
        printf("Passed: %d\n", pass_count);
        printf("Failed: %d\n", test_count - pass_count);
        printf("Pass rate: %.1f%%\n", pass_percentage);

        // Determine overall system status
        if (pass_percentage >= 95.0f) {
            printf("Status: ✓ CHIP VALIDATED - Excellent quality\n");
        } else if (pass_percentage >= 90.0f) {
            printf("Status: ⚠ CHIP MARGINAL - Review required\n");
        } else {
            printf("Status: ✗ CHIP FAILED - Reject chip\n");
        }
    } else {
        printf("No voltage readings processed.\n");
    }

    return 0;
}

/*
 * REFERENCE SOLUTION NOTES:
 *
 * 1. Data Type Selection:
 *    - float: For voltage readings (precision needed for ±5% tolerance)
 *    - int: For counters (whole numbers only)
 *    - char: For status flags (single character is sufficient)
 *
 * 2. Validation Logic:
 *    - Check both upper and lower bounds
 *    - Provide specific feedback for failures
 *    - Calculate statistics for quality assessment
 *
 * 3. User Experience:
 *    - Clear prompts and instructions
 *    - Formatted output with appropriate precision
 *    - Summary statistics for batch validation
 *
 * 4. Error Handling:
 *    - Sentinel value (-1) for exit
 *    - Input validation with scanf return value checking
 *    - Buffer clearing for invalid inputs
 *    - Graceful handling of edge cases
 *
 * 5. Engineering Best Practices:
 *    - Use of #define for constants
 *    - Meaningful variable names
 *    - Comprehensive comments
 *    - Proper formatting and indentation
 *
 * TESTING SUGGESTIONS:
 * - Test with values inside range: 1.75, 1.8, 1.85
 * - Test with values outside range: 1.5, 2.0
 * - Test boundary conditions: 1.71, 1.89
 * - Test with multiple readings to verify statistics
 * - Test with invalid inputs (letters, symbols)
 */

