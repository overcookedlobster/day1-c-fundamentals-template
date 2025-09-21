/*
 * Day 1 Task 2: Power Consumption Calculator - REFERENCE SOLUTION
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

// Define power specification constants
#define MAX_POWER_WATTS     2.0f    // Maximum power limit
#define MIN_VOLTAGE         1.5f    // Minimum operating voltage
#define MAX_VOLTAGE         2.0f    // Maximum operating voltage
#define MIN_CURRENT         0.1f    // Minimum current
#define MAX_CURRENT         1.5f    // Maximum current

// Power efficiency categories
#define EFFICIENT_THRESHOLD   1.0f  // Power below this is "efficient"
#define MODERATE_THRESHOLD    1.5f  // Power below this is "moderate"

int main() {
    // Declare variables for calculations
    float voltage;              // input voltage in volts
    float current;              // input current in amperes
    float power;                // calculated power in watts
    int calculation_count = 0;  // number of calculations performed
    float total_power = 0.0f;   // sum of all power calculations
    char continue_choice;       // user choice to continue ('y'/'n')

    printf("=== Chip Power Consumption Calculator ===\n");
    printf("Power Limits: %.2fW maximum\n", MAX_POWER_WATTS);
    printf("Voltage Range: %.1fV - %.1fV\n", MIN_VOLTAGE, MAX_VOLTAGE);
    printf("Current Range: %.1fA - %.1fA\n\n", MIN_CURRENT, MAX_CURRENT);

    // Initialize counters and accumulators
    calculation_count = 0;
    total_power = 0.0f;

    do {
        printf("--- Power Calculation #%d ---\n", calculation_count + 1);

        // Get voltage input with validation
        do {
            printf("Enter voltage (V): ");
            if (scanf("%f", &voltage) != 1) {
                printf("Error: Invalid input. Please enter a numeric value.\n");
                while (getchar() != '\n'); // Clear input buffer
                continue;
            }

            // Validate voltage range
            if (voltage < MIN_VOLTAGE) {
                printf("Error: Voltage %.2fV is below minimum (%.1fV)\n", voltage, MIN_VOLTAGE);
            } else if (voltage > MAX_VOLTAGE) {
                printf("Error: Voltage %.2fV is above maximum (%.1fV)\n", voltage, MAX_VOLTAGE);
            }
        } while (voltage < MIN_VOLTAGE || voltage > MAX_VOLTAGE);

        // Get current input with validation
        do {
            printf("Enter current (A): ");
            if (scanf("%f", &current) != 1) {
                printf("Error: Invalid input. Please enter a numeric value.\n");
                while (getchar() != '\n'); // Clear input buffer
                continue;
            }

            // Validate current range
            if (current < MIN_CURRENT) {
                printf("Error: Current %.2fA is below minimum (%.1fA)\n", current, MIN_CURRENT);
            } else if (current > MAX_CURRENT) {
                printf("Error: Current %.2fA is above maximum (%.1fA)\n", current, MAX_CURRENT);
            }
        } while (current < MIN_CURRENT || current > MAX_CURRENT);

        // Calculate power consumption
        power = voltage * current;

        // Update statistics
        calculation_count++;
        total_power += power;

        // Display calculation results
        printf("\n--- Results ---\n");
        printf("Voltage: %.2fV\n", voltage);
        printf("Current: %.2fA\n", current);
        printf("Power: %.3fW\n", power);

        // Analyze power consumption level
        if (power <= EFFICIENT_THRESHOLD) {
            printf("Status: ✓ EFFICIENT - Low power consumption\n");
        } else if (power <= MODERATE_THRESHOLD) {
            printf("Status: ⚠ MODERATE - Acceptable power consumption\n");
        } else if (power <= MAX_POWER_WATTS) {
            printf("Status: ⚠ HIGH - Near maximum power limit\n");
        } else {
            printf("Status: ✗ EXCESSIVE - Exceeds power limit!\n");
        }

        // Check against absolute power limit
        if (power > MAX_POWER_WATTS) {
            printf("WARNING: Power %.3fW exceeds limit of %.2fW!\n", power, MAX_POWER_WATTS);
            printf("Chip may overheat or damage power supply.\n");
        }

        // Calculate power density (power per volt)
        float power_density = power / voltage;
        printf("Power density: %.3fW/V\n", power_density);

        // Ask user if they want to continue
        printf("\nCalculate another power reading? (y/n): ");
        scanf(" %c", &continue_choice); // Note the space before %c to skip whitespace

        printf("\n");

    } while (continue_choice == 'y' || continue_choice == 'Y');

    // Display final statistics
    if (calculation_count > 0) {
        float average_power = total_power / calculation_count;

        printf("=== Power Analysis Summary ===\n");
        printf("Total calculations: %d\n", calculation_count);
        printf("Total power consumption: %.3fW\n", total_power);
        printf("Average power consumption: %.3fW\n", average_power);

        // Provide overall assessment
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

        // Calculate power budget utilization
        float budget_utilization = (average_power / MAX_POWER_WATTS) * 100.0f;
        printf("Power budget utilization: %.1f%%\n", budget_utilization);

    } else {
        printf("No power calculations performed.\n");
    }

    printf("\nThank you for using the Power Calculator!\n");
    return 0;
}

/*
 * REFERENCE SOLUTION NOTES:
 *
 * 1. Input Validation Strategy:
 *    - Use do-while loops for input validation
 *    - Check scanf return value for input errors
 *    - Clear input buffer after invalid input
 *    - Provide clear error messages with specific values
 *    - Continue prompting until valid input is received
 *
 * 2. Mathematical Calculations:
 *    - Power = Voltage × Current (Ohm's Law)
 *    - Power density = Power / Voltage (efficiency metric)
 *    - Budget utilization = (Power / Max Power) × 100%
 *    - Statistical calculations for multiple readings
 *
 * 3. User Experience Design:
 *    - Clear section headers and formatting
 *    - Progressive disclosure of information
 *    - Meaningful status messages and warnings
 *    - Comprehensive summary information
 *
 * 4. Data Management:
 *    - Track multiple calculations for statistical analysis
 *    - Accumulate totals for average calculations
 *    - Provide comprehensive summary information
 *    - Handle edge cases gracefully
 *
 * 5. Engineering Context:
 *    - Power limits based on realistic chip specifications
 *    - Efficiency categories relevant to chip design
 *    - Warnings for potentially dangerous conditions
 *    - Professional-quality output formatting
 *
 * 6. Error Handling:
 *    - Input validation with clear error messages
 *    - Range checking for all parameters
 *    - Buffer management for character input
 *    - Graceful handling of invalid inputs
 *
 * TESTING SUGGESTIONS:
 * - Test with normal operating conditions: 1.8V, 0.5A
 * - Test boundary conditions: minimum and maximum values
 * - Test invalid inputs: negative values, out-of-range values
 * - Test multiple calculations to verify statistics
 * - Test edge case: exactly at power limit
 * - Test character input validation
 * - Test very large and very small numbers
 *
 * EXTENSION IDEAS:
 * - Add temperature coefficient calculations
 * - Include power efficiency curves
 * - Support for different chip configurations
 * - Export results to file for further analysis
 * - Add graphical power consumption trends
 */

