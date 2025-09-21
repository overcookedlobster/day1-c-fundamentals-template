/*
 * Day 1 Task 2: Power Consumption Calculator
 * Chip Parameter Validation System
 *
 * Learning Objectives:
 * - Use printf/scanf for user input and formatted output
 * - Perform mathematical operations for engineering calculations
 * - Implement input validation and error handling
 * - Work with multiple data types in calculations
 *
 * Real-World Context:
 * Power consumption (P = V × I) is critical for chip validation.
 * Engineers must verify that chips operate within power budgets
 * and thermal limits. This calculator helps validate power specs.
 */

#include <stdio.h>
#include <stdbool.h>
#include "../include/validation.h"

// TODO 1: Define power specification constants
// Hint: These represent typical chip power limits
// TODO: Students should understand these power specifications
#define MAX_POWER_WATTS     2.0f    // TODO: Define maximum power limit
#define MIN_VOLTAGE         1.5f    // TODO: Define minimum operating voltage
#define MAX_VOLTAGE         2.0f    // TODO: Define maximum operating voltage
#define MIN_CURRENT         0.1f    // TODO: Define minimum current
#define MAX_CURRENT         1.5f    // TODO: Define maximum current

// Power efficiency categories
#define EFFICIENT_THRESHOLD   1.0f  // TODO: Power below this is "efficient"
#define MODERATE_THRESHOLD    1.5f  // TODO: Power below this is "moderate"

int main() {
    // TODO 2: Declare variables for calculations
    // Hint: Consider precision requirements for each measurement
    float voltage = 0.0f;        // TODO: Students should understand this declaration
    float current = 0.0f;        // TODO: Students should understand this declaration
    float power = 0.0f;          // TODO: Students should understand this declaration
    int calculation_count = 0;   // TODO: Students should understand this declaration
    /* TODO: float total_power - sum of all power calculations */
    /* TODO: char continue_choice - user choice to continue ('y'/'n') */

    printf("=== Chip Power Consumption Calculator ===\n");
    printf("Power Limits: %.2fW maximum\n", MAX_POWER_WATTS);
    printf("Voltage Range: %.1fV - %.1fV\n", MIN_VOLTAGE, MAX_VOLTAGE);
    printf("Current Range: %.1fA - %.1fA\n\n", MIN_CURRENT, MAX_CURRENT);

    /* TODO: Initialize counters and accumulators */

    do {
        printf("--- Power Calculation #%d ---\n", calculation_count + 1);

        // TODO 3: Get voltage input with validation
        // Hint: Use a loop to ensure valid input
        do {
            printf("Enter voltage (V): ");
            /* TODO: Read voltage using scanf */

            // TODO 4: Validate voltage range
            if (/* TODO: Check if voltage is below minimum */) {
                printf("Error: Voltage %.2fV is below minimum (%.1fV)\n", voltage, MIN_VOLTAGE);
            } else if (/* TODO: Check if voltage is above maximum */) {
                printf("Error: Voltage %.2fV is above maximum (%.1fV)\n", voltage, MAX_VOLTAGE);
            }
        } while (/* TODO: Continue loop while voltage is out of range */);

        // TODO 5: Get current input with validation
        // Hint: Similar validation pattern as voltage
        do {
            printf("Enter current (A): ");
            /* TODO: Read current using scanf */

            // TODO 6: Validate current range
            if (/* TODO: Check if current is below minimum */) {
                printf("Error: Current %.2fA is below minimum (%.1fA)\n", current, MIN_CURRENT);
            } else if (/* TODO: Check if current is above maximum */) {
                printf("Error: Current %.2fA is above maximum (%.1fA)\n", current, MAX_CURRENT);
            }
        } while (/* TODO: Continue loop while current is out of range */);

        // TODO 7: Calculate power consumption
        /* TODO: Calculate power = voltage × current */

        // TODO 8: Update statistics
        /* TODO: Increment calculation_count */
        /* TODO: Add power to total_power */

        // TODO 9: Display calculation results
        printf("\n--- Results ---\n");
        printf("Voltage: %.2fV\n", voltage);
        printf("Current: %.2fA\n", current);
        printf("Power: %.3fW\n", power);

        // TODO 10: Analyze power consumption level
        // Hint: Categorize power as efficient, moderate, or high
        if (/* TODO: Check if power is below efficient threshold */) {
            printf("Status: ✓ EFFICIENT - Low power consumption\n");
        } else if (/* TODO: Check if power is below moderate threshold */) {
            printf("Status: ⚠ MODERATE - Acceptable power consumption\n");
        } else if (/* TODO: Check if power is below maximum */) {
            printf("Status: ⚠ HIGH - Near maximum power limit\n");
        } else {
            printf("Status: ✗ EXCESSIVE - Exceeds power limit!\n");
        }

        // TODO 11: Check against absolute power limit
        if (/* TODO: Check if power exceeds maximum */) {
            printf("WARNING: Power %.3fW exceeds limit of %.2fW!\n", power, MAX_POWER_WATTS);
            printf("Chip may overheat or damage power supply.\n");
        }

        // TODO 12: Calculate power density (power per volt)
        // Hint: This helps understand efficiency at different voltages
        float power_density = /* TODO: Calculate power / voltage */;
        printf("Power density: %.3fW/V\n", power_density);

        // TODO 13: Ask user if they want to continue
        printf("\nCalculate another power reading? (y/n): ");
        /* TODO: Read continue_choice using scanf with %c format */

        // Clear input buffer (important for character input)
        while (getchar() != '\n');

        printf("\n");

    } while (/* TODO: Continue while user enters 'y' or 'Y' */);

    // TODO 14: Display final statistics
    if (calculation_count > 0) {
        /* TODO: Calculate average_power = total_power / calculation_count */
        float average_power = /* TODO: Calculate average */;

        printf("=== Power Analysis Summary ===\n");
        printf("Total calculations: %d\n", calculation_count);
        printf("Total power consumption: %.3fW\n", total_power);
        printf("Average power consumption: %.3fW\n", average_power);

        // TODO 15: Provide overall assessment
        // Hint: Base assessment on average power consumption
        if (average_power <= EFFICIENT_THRESHOLD) {
            printf("Overall Assessment: ✓ EFFICIENT DESIGN\n");
            printf("Chip demonstrates excellent power efficiency.\n");
        } else if (average_power <= MODERATE_THRESHOLD) {
            printf("Overall Assessment: ⚠ MODERATE EFFICIENCY\n");
            printf("Chip power consumption is acceptable.\n");
        } else {
            printf("Overall Assessment: ⚠ HIGH POWER CONSUMPTION\n");
            printf("Consider power optimization techniques.\n");
        }

        // TODO 16: Calculate power budget utilization
        float budget_utilization = /* TODO: Calculate (average_power / MAX_POWER_WATTS) * 100 */;
        printf("Power budget utilization: %.1f%%\n", budget_utilization);

    } else {
        printf("No power calculations performed.\n");
    }

    printf("\nThank you for using the Power Calculator!\n");
    return 0;
}

/*
 * IMPLEMENTATION NOTES:
 *
 * 1. Input Validation Strategy:
 *    - Use do-while loops for input validation
 *    - Provide clear error messages with specific values
 *    - Continue prompting until valid input is received
 *
 * 2. Mathematical Calculations:
 *    - Power = Voltage × Current (Ohm's Law)
 *    - Power density = Power / Voltage (efficiency metric)
 *    - Budget utilization = (Power / Max Power) × 100%
 *
 * 3. User Experience Design:
 *    - Clear section headers and formatting
 *    - Progressive disclosure of information
 *    - Meaningful status messages and warnings
 *
 * 4. Data Management:
 *    - Track multiple calculations for statistical analysis
 *    - Accumulate totals for average calculations
 *    - Provide comprehensive summary information
 *
 * 5. Engineering Context:
 *    - Power limits based on realistic chip specifications
 *    - Efficiency categories relevant to chip design
 *    - Warnings for potentially dangerous conditions
 *
 * TESTING SUGGESTIONS:
 * - Test with normal operating conditions: 1.8V, 0.5A
 * - Test boundary conditions: minimum and maximum values
 * - Test invalid inputs: negative values, out-of-range values
 * - Test multiple calculations to verify statistics
 * - Test edge case: exactly at power limit
 *
 * EXTENSION IDEAS:
 * - Add temperature coefficient calculations
 * - Include power efficiency curves
 * - Support for different chip configurations
 * - Export results to file for further analysis
 */

