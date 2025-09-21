/*
 * Day 1 Task 1: Voltage Checker
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

// TODO 1: Define voltage specification constants
// Hint: Use #define or const float for these values
// - NOMINAL_VOLTAGE: 1.8V
// - TOLERANCE_PERCENT: 5.0%
// - MIN_VOLTAGE: Calculate from nominal and tolerance
// - MAX_VOLTAGE: Calculate from nominal and tolerance

#define NOMINAL_VOLTAGE     /* TODO: Define 1.8V */
#define TOLERANCE_PERCENT   /* TODO: Define 5.0% */
#define MIN_VOLTAGE         /* TODO: Calculate minimum acceptable voltage */
#define MAX_VOLTAGE         /* TODO: Calculate maximum acceptable voltage */

int main() {
    // TODO 2: Declare variables with appropriate data types
    // Hint: Consider what type of data each variable will store
    /* TODO: float voltage_reading - for precise voltage measurements */
    /* TODO: int test_count - for counting number of tests */
    /* TODO: int pass_count - for counting passed tests */
    /* TODO: char status - for storing pass/fail status ('P' or 'F') */

    printf("=== Chip Voltage Validation System ===\n");
    printf("Nominal Voltage: %.2fV (±%.1f%%)\n", NOMINAL_VOLTAGE, TOLERANCE_PERCENT);
    printf("Acceptable Range: %.2fV - %.2fV\n\n", MIN_VOLTAGE, MAX_VOLTAGE);

    // TODO 3: Implement input loop for multiple voltage readings
    // Hint: Use a do-while loop or while loop with sentinel value
    printf("Enter voltage readings (enter -1 to quit):\n");

    /* TODO: Initialize counters */

    while (1) {
        printf("Voltage reading: ");

        // TODO 4: Get voltage input from user
        // Hint: Use scanf with appropriate format specifier for float
        /* TODO: Read voltage_reading using scanf */

        // Check for exit condition
        if (voltage_reading == -1.0) {
            break;
        }

        // TODO 5: Validate input range and update counters
        // Hint: Check if voltage_reading is between MIN_VOLTAGE and MAX_VOLTAGE
        /* TODO: Increment test_count */

        /* TODO: Check if voltage is within acceptable range */
        if (/* TODO: Add condition for voltage within range */) {
            /* TODO: Set status to 'P' for pass */
            /* TODO: Increment pass_count */
            printf("✓ PASS: Voltage %.2fV is within acceptable range\n", voltage_reading);
        } else {
            /* TODO: Set status to 'F' for fail */
            printf("✗ FAIL: Voltage %.2fV is outside acceptable range\n", voltage_reading);

            // TODO 6: Provide specific feedback about the failure
            // Hint: Tell user if voltage is too high or too low
            if (/* TODO: Check if voltage is too low */) {
                printf("  → Voltage is %.2fV below minimum (%.2fV)\n",
                       MIN_VOLTAGE - voltage_reading, MIN_VOLTAGE);
            } else if (/* TODO: Check if voltage is too high */) {
                printf("  → Voltage is %.2fV above maximum (%.2fV)\n",
                       voltage_reading - MAX_VOLTAGE, MAX_VOLTAGE);
            }
        }
        printf("\n");
    }

    // TODO 7: Display final statistics
    // Hint: Calculate pass percentage and display summary
    if (test_count > 0) {
        /* TODO: Calculate pass_percentage as float */
        float pass_percentage = /* TODO: Calculate percentage */;

        printf("=== Validation Summary ===\n");
        printf("Total tests: %d\n", test_count);
        printf("Passed: %d\n", pass_count);
        printf("Failed: %d\n", /* TODO: Calculate failed count */);
        printf("Pass rate: %.1f%%\n", pass_percentage);

        // TODO 8: Determine overall system status
        // Hint: Consider what pass rate indicates good chip quality
        if (pass_percentage >= 95.0) {
            printf("Status: ✓ CHIP VALIDATED - Excellent quality\n");
        } else if (pass_percentage >= 90.0) {
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
 * IMPLEMENTATION NOTES:
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
 *    - Input validation (basic level for this task)
 *    - Graceful handling of edge cases
 *
 * TESTING SUGGESTIONS:
 * - Test with values inside range: 1.75, 1.8, 1.85
 * - Test with values outside range: 1.5, 2.0
 * - Test boundary conditions: 1.71, 1.89
 * - Test with multiple readings to verify statistics
 */

