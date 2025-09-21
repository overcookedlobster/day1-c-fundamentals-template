/*
 * Day 1 Task 5: Safety Validator - STUDENT TEMPLATE
 * Chip Parameter Validation System
 *
 * Learning Objectives:
 * - Implement comprehensive input validation and error handling
 * - Practice memory safety and bounds checking
 * - Use defensive programming techniques
 * - Handle edge cases and invalid inputs gracefully
 *
 * Real-World Context:
 * Safety-critical validation systems must handle all possible inputs
 * gracefully and never crash or produce incorrect results.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/validation.h"

// TODO: Define safety limits and constants
#define MAX_INPUT_LENGTH 256
#define MAX_READINGS 100

// TODO: Define input validation result codes
typedef enum {
    INPUT_VALID = 0,
    INPUT_INVALID_FORMAT,
    INPUT_OUT_OF_RANGE,
    INPUT_EMPTY
} InputValidationResult;

// TODO: Implement safe input validation function
InputValidationResult validate_float_input(const char* input, float* result, float min_val, float max_val) {
    // TODO: Add comprehensive input validation
    // - Check for null pointers
    // - Check for empty input
    // - Use strtof for safe conversion
    // - Validate range

    if (input == NULL || result == NULL) {
        return INPUT_INVALID_FORMAT;
    }

    // Basic implementation - students should enhance this
    *result = atof(input);

    if (*result < min_val || *result > max_val) {
        return INPUT_OUT_OF_RANGE;
    }

    return INPUT_VALID;
}

// TODO: Implement safe string operations
bool safe_string_copy(char* dest, const char* src, size_t dest_size) {
    // TODO: Add null pointer checks
    // TODO: Add bounds checking
    // TODO: Ensure null termination

    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }

    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    return true;
}

int main() {
    printf("=== Safety Validator: Robust Input Handling ===\n");
    printf("This program demonstrates safe input validation techniques.\n\n");

    // TODO: Declare variables with safe initialization
    char input_buffer[MAX_INPUT_LENGTH];
    float voltage = 0.0f;
    float current = 0.0f;
    float temperature = 0.0f;
    int num_readings = 0;
    bool continue_testing = true;

    // TODO: Add arrays for storing readings with bounds checking
    float voltage_readings[MAX_READINGS];
    float current_readings[MAX_READINGS];

    printf("Enter chip parameters for validation.\n");
    printf("Safety limits: Voltage [1.5-2.0V], Current [0.1-1.5A], Temperature [-40-85°C]\n\n");

    while (continue_testing && num_readings < MAX_READINGS) {
        printf("--- Reading #%d ---\n", num_readings + 1);

        // TODO: Implement safe voltage input
        InputValidationResult result;
        do {
            printf("Enter voltage (V): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                printf("Error: Failed to read input. Exiting.\n");
                return 1;
            }

            // Remove newline
            size_t len = strlen(input_buffer);
            if (len > 0 && input_buffer[len-1] == '\n') {
                input_buffer[len-1] = '\0';
            }

            result = validate_float_input(input_buffer, &voltage, 1.5f, 2.0f);
            if (result != INPUT_VALID) {
                printf("Error: Invalid voltage input. Please try again.\n");
            }
        } while (result != INPUT_VALID);

        // TODO: Implement safe current input (similar to voltage)
        do {
            printf("Enter current (A): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                printf("Error: Failed to read input. Exiting.\n");
                return 1;
            }

            // Remove newline
            size_t len = strlen(input_buffer);
            if (len > 0 && input_buffer[len-1] == '\n') {
                input_buffer[len-1] = '\0';
            }

            result = validate_float_input(input_buffer, &current, 0.1f, 1.5f);
            if (result != INPUT_VALID) {
                printf("Error: Invalid current input. Please try again.\n");
            }
        } while (result != INPUT_VALID);

        // TODO: Implement safe temperature input
        do {
            printf("Enter temperature (°C): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                printf("Error: Failed to read input. Exiting.\n");
                return 1;
            }

            // Remove newline
            size_t len = strlen(input_buffer);
            if (len > 0 && input_buffer[len-1] == '\n') {
                input_buffer[len-1] = '\0';
            }

            result = validate_float_input(input_buffer, &temperature, -40.0f, 85.0f);
            if (result != INPUT_VALID) {
                printf("Error: Invalid temperature input. Please try again.\n");
            }
        } while (result != INPUT_VALID);

        // TODO: Store readings safely with bounds checking
        if (num_readings < MAX_READINGS) {
            voltage_readings[num_readings] = voltage;
            current_readings[num_readings] = current;

            // TODO: Validate parameters and provide feedback
            float power = voltage * current;
            bool voltage_safe = (voltage >= 1.5f && voltage <= 2.0f);
            bool current_safe = (current >= 0.1f && current <= 1.5f);
            bool power_safe = (power <= 2.0f);

            printf("\n--- Safety Analysis ---\n");
            printf("Voltage: %.2fV %s\n", voltage, voltage_safe ? "✓ SAFE" : "⚠ UNSAFE");
            printf("Current: %.2fA %s\n", current, current_safe ? "✓ SAFE" : "⚠ UNSAFE");
            printf("Power: %.3fW %s\n", power, power_safe ? "✓ SAFE" : "⚠ UNSAFE");

            if (voltage_safe && current_safe && power_safe) {
                printf("Overall Status: ✓ ALL PARAMETERS SAFE\n");
            } else {
                printf("Overall Status: ⚠ SOME PARAMETERS UNSAFE\n");
            }

            num_readings++;
        }

        // TODO: Ask to continue with safe input handling
        char continue_choice;
        do {
            printf("\nContinue testing? (y/n): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                continue_testing = false;
                break;
            }

            if (strlen(input_buffer) >= 2) {
                continue_choice = input_buffer[0];
                if (continue_choice == 'y' || continue_choice == 'Y') {
                    continue_testing = true;
                    break;
                } else if (continue_choice == 'n' || continue_choice == 'N') {
                    continue_testing = false;
                    break;
                } else {
                    printf("Please enter 'y' for yes or 'n' for no.\n");
                }
            }
        } while (true);

        printf("\n");
    }

    // TODO: Generate safety summary with bounds checking
    if (num_readings > 0) {
        printf("=== Safety Validation Summary ===\n");
        printf("Total readings processed: %d\n", num_readings);

        // TODO: Calculate statistics safely
        float voltage_sum = 0.0f;
        float current_sum = 0.0f;
        int safe_readings = 0;

        for (int i = 0; i < num_readings; i++) {
            voltage_sum += voltage_readings[i];
            current_sum += current_readings[i];

            // Count safe readings
            float power = voltage_readings[i] * current_readings[i];
            bool reading_safe = (voltage_readings[i] >= 1.5f && voltage_readings[i] <= 2.0f) &&
                               (current_readings[i] >= 0.1f && current_readings[i] <= 1.5f) &&
                               (power <= 2.0f);
            if (reading_safe) {
                safe_readings++;
            }
        }

        printf("Average voltage: %.2fV\n", voltage_sum / num_readings);
        printf("Average current: %.2fA\n", current_sum / num_readings);

        float safety_rate = ((float)safe_readings / num_readings) * 100.0f;
        printf("Safety rate: %.1f%% (%d/%d readings safe)\n", safety_rate, safe_readings, num_readings);

        if (safety_rate >= 95.0f) {
            printf("Safety Assessment: ✓ EXCELLENT\n");
        } else if (safety_rate >= 80.0f) {
            printf("Safety Assessment: ⚠ ACCEPTABLE\n");
        } else {
            printf("Safety Assessment: ✗ CONCERNING\n");
        }
    } else {
        printf("No valid readings processed.\n");
    }

    printf("\nSafety validation completed.\n");
    return 0;
}

/*
 * SAFETY VALIDATOR TEMPLATE NOTES:
 *
 * Students should enhance this template by:
 *
 * 1. IMPROVING INPUT VALIDATION:
 *    - Use strtof() instead of atof() for better error detection
 *    - Add comprehensive error checking
 *    - Handle edge cases and special values
 *    - Implement timeout for input operations
 *
 * 2. ADDING MEMORY SAFETY:
 *    - Implement bounds checking for all arrays
 *    - Add overflow detection for calculations
 *    - Use safe string functions consistently
 *    - Add memory allocation error handling
 *
 * 3. ENHANCING ERROR HANDLING:
 *    - Provide specific error messages
 *    - Implement graceful degradation
 *    - Add logging capabilities
 *    - Handle system call failures
 *
 * 4. IMPROVING USER EXPERIENCE:
 *    - Add input format validation
 *    - Provide clear instructions
 *    - Add progress indicators
 *    - Implement undo/retry functionality
 *
 * TESTING SCENARIOS:
 * - Valid inputs within normal ranges
 * - Invalid input formats (letters, symbols)
 * - Out-of-range values
 * - Empty inputs
 * - Very large numbers
 * - Buffer overflow attempts
 *
 * COMPILATION:
 * gcc -Wall -Wextra -std=c11 -g -Iinclude -o safety_validator src/safety_validator.c
 */

