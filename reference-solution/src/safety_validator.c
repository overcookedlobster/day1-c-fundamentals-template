/*
 * Day 1 Task 5: Safety Validator - REFERENCE SOLUTION
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
 * gracefully and never crash or produce incorrect results. This program
 * demonstrates robust input validation for chip parameter testing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <errno.h>
#include "../include/validation.h"

// Safety limits and constants
#define MAX_INPUT_LENGTH 256
#define MAX_READINGS 1000
#define SAFETY_MARGIN 0.1f

// Input validation result codes
typedef enum {
    INPUT_VALID = 0,
    INPUT_INVALID_FORMAT,
    INPUT_OUT_OF_RANGE,
    INPUT_TOO_LONG,
    INPUT_EMPTY,
    INPUT_OVERFLOW
} InputValidationResult;

// Function prototypes
InputValidationResult validate_float_input(const char* input, float* result, float min_val, float max_val);
InputValidationResult validate_int_input(const char* input, int* result, int min_val, int max_val);
bool safe_string_copy(char* dest, const char* src, size_t dest_size);
void clear_input_buffer(void);
void print_validation_error(InputValidationResult error, const char* parameter_name);

int main() {
    printf("=== Safety Validator: Robust Input Handling ===\n");
    printf("This program demonstrates safe input validation techniques.\n\n");

    // Safe buffer for input
    char input_buffer[MAX_INPUT_LENGTH];
    float voltage, current, temperature;
    int num_readings = 0;
    bool continue_testing = true;

    // Arrays to store readings (with bounds checking)
    float voltage_readings[MAX_READINGS];
    float current_readings[MAX_READINGS];
    float temperature_readings[MAX_READINGS];

    printf("Enter chip parameters for validation.\n");
    printf("Safety limits: Voltage [1.5-2.0V], Current [0.1-1.5A], Temperature [-40-85°C]\n\n");

    while (continue_testing && num_readings < MAX_READINGS) {
        printf("--- Reading #%d ---\n", num_readings + 1);

        // Safe voltage input with comprehensive validation
        InputValidationResult result;
        do {
            printf("Enter voltage (V): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                printf("Error: Failed to read input. Exiting.\n");
                return 1;
            }

            // Remove newline if present
            size_t len = strlen(input_buffer);
            if (len > 0 && input_buffer[len-1] == '\n') {
                input_buffer[len-1] = '\0';
            }

            result = validate_float_input(input_buffer, &voltage, 1.5f, 2.0f);
            if (result != INPUT_VALID) {
                print_validation_error(result, "voltage");
            }
        } while (result != INPUT_VALID);

        // Safe current input with validation
        do {
            printf("Enter current (A): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                printf("Error: Failed to read input. Exiting.\n");
                return 1;
            }

            // Remove newline if present
            size_t len = strlen(input_buffer);
            if (len > 0 && input_buffer[len-1] == '\n') {
                input_buffer[len-1] = '\0';
            }

            result = validate_float_input(input_buffer, &current, 0.1f, 1.5f);
            if (result != INPUT_VALID) {
                print_validation_error(result, "current");
            }
        } while (result != INPUT_VALID);

        // Safe temperature input with validation
        do {
            printf("Enter temperature (°C): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                printf("Error: Failed to read input. Exiting.\n");
                return 1;
            }

            // Remove newline if present
            size_t len = strlen(input_buffer);
            if (len > 0 && input_buffer[len-1] == '\n') {
                input_buffer[len-1] = '\0';
            }

            result = validate_float_input(input_buffer, &temperature, -40.0f, 85.0f);
            if (result != INPUT_VALID) {
                print_validation_error(result, "temperature");
            }
        } while (result != INPUT_VALID);

        // Store readings safely (with bounds checking)
        if (num_readings < MAX_READINGS) {
            voltage_readings[num_readings] = voltage;
            current_readings[num_readings] = current;
            temperature_readings[num_readings] = temperature;

            // Calculate power with overflow checking
            float power = voltage * current;
            if (power > FLT_MAX / 2.0f) {  // Check for potential overflow
                printf("Warning: Power calculation may overflow\n");
            }

            // Validate against safety limits
            bool voltage_safe = (voltage >= 1.5f + SAFETY_MARGIN) && (voltage <= 2.0f - SAFETY_MARGIN);
            bool current_safe = (current >= 0.1f + SAFETY_MARGIN) && (current <= 1.5f - SAFETY_MARGIN);
            bool temp_safe = (temperature >= -40.0f + SAFETY_MARGIN) && (temperature <= 85.0f - SAFETY_MARGIN);
            bool power_safe = (power <= 2.0f - SAFETY_MARGIN);

            printf("\n--- Safety Analysis ---\n");
            printf("Voltage: %.2fV %s\n", voltage, voltage_safe ? "✓ SAFE" : "⚠ MARGINAL");
            printf("Current: %.2fA %s\n", current, current_safe ? "✓ SAFE" : "⚠ MARGINAL");
            printf("Temperature: %.1f°C %s\n", temperature, temp_safe ? "✓ SAFE" : "⚠ MARGINAL");
            printf("Power: %.3fW %s\n", power, power_safe ? "✓ SAFE" : "⚠ MARGINAL");

            if (voltage_safe && current_safe && temp_safe && power_safe) {
                printf("Overall Status: ✓ ALL PARAMETERS SAFE\n");
            } else {
                printf("Overall Status: ⚠ SOME PARAMETERS MARGINAL\n");
            }

            num_readings++;
        } else {
            printf("Warning: Maximum number of readings reached (%d)\n", MAX_READINGS);
            break;
        }

        // Ask to continue with safe input handling
        char continue_choice;
        do {
            printf("\nContinue testing? (y/n): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                continue_testing = false;
                break;
            }

            if (strlen(input_buffer) >= 2) {  // At least one character plus newline
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
            } else {
                printf("Please enter 'y' for yes or 'n' for no.\n");
            }
        } while (true);

        printf("\n");
    }

    // Generate safety summary with bounds checking
    if (num_readings > 0) {
        printf("=== Safety Validation Summary ===\n");
        printf("Total readings processed: %d\n", num_readings);

        // Calculate statistics safely
        float voltage_sum = 0.0f, current_sum = 0.0f, temp_sum = 0.0f;
        int safe_readings = 0;

        for (int i = 0; i < num_readings; i++) {
            // Safe accumulation with overflow checking
            if (voltage_sum <= FLT_MAX - voltage_readings[i]) {
                voltage_sum += voltage_readings[i];
            }
            if (current_sum <= FLT_MAX - current_readings[i]) {
                current_sum += current_readings[i];
            }
            if (temp_sum <= FLT_MAX - temperature_readings[i]) {
                temp_sum += temperature_readings[i];
            }

            // Count safe readings
            bool reading_safe = (voltage_readings[i] >= 1.5f + SAFETY_MARGIN) &&
                               (voltage_readings[i] <= 2.0f - SAFETY_MARGIN) &&
                               (current_readings[i] >= 0.1f + SAFETY_MARGIN) &&
                               (current_readings[i] <= 1.5f - SAFETY_MARGIN) &&
                               (temperature_readings[i] >= -40.0f + SAFETY_MARGIN) &&
                               (temperature_readings[i] <= 85.0f - SAFETY_MARGIN);
            if (reading_safe) {
                safe_readings++;
            }
        }

        // Safe division for averages
        if (num_readings > 0) {
            printf("Average voltage: %.2fV\n", voltage_sum / num_readings);
            printf("Average current: %.2fA\n", current_sum / num_readings);
            printf("Average temperature: %.1f°C\n", temp_sum / num_readings);
        }

        float safety_rate = ((float)safe_readings / num_readings) * 100.0f;
        printf("Safety rate: %.1f%% (%d/%d readings safe)\n", safety_rate, safe_readings, num_readings);

        if (safety_rate >= 95.0f) {
            printf("Safety Assessment: ✓ EXCELLENT - All parameters well within limits\n");
        } else if (safety_rate >= 80.0f) {
            printf("Safety Assessment: ⚠ ACCEPTABLE - Most parameters safe\n");
        } else {
            printf("Safety Assessment: ✗ CONCERNING - Many parameters near limits\n");
        }
    } else {
        printf("No valid readings processed.\n");
    }

    printf("\nSafety validation completed.\n");
    return 0;
}

// Comprehensive float input validation
InputValidationResult validate_float_input(const char* input, float* result, float min_val, float max_val) {
    if (input == NULL || result == NULL) {
        return INPUT_INVALID_FORMAT;
    }

    // Check for empty input
    if (strlen(input) == 0) {
        return INPUT_EMPTY;
    }

    // Check input length
    if (strlen(input) >= MAX_INPUT_LENGTH - 1) {
        return INPUT_TOO_LONG;
    }

    // Use strtof for safe conversion
    char* endptr;
    errno = 0;
    float value = strtof(input, &endptr);

    // Check for conversion errors
    if (errno == ERANGE) {
        return INPUT_OVERFLOW;
    }

    // Check if entire string was consumed
    if (*endptr != '\0') {
        return INPUT_INVALID_FORMAT;
    }

    // Check for range
    if (value < min_val || value > max_val) {
        return INPUT_OUT_OF_RANGE;
    }

    *result = value;
    return INPUT_VALID;
}

// Comprehensive integer input validation
InputValidationResult validate_int_input(const char* input, int* result, int min_val, int max_val) {
    if (input == NULL || result == NULL) {
        return INPUT_INVALID_FORMAT;
    }

    // Check for empty input
    if (strlen(input) == 0) {
        return INPUT_EMPTY;
    }

    // Use strtol for safe conversion
    char* endptr;
    errno = 0;
    long value = strtol(input, &endptr, 10);

    // Check for conversion errors
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        return INPUT_OVERFLOW;
    }

    // Check if entire string was consumed
    if (*endptr != '\0') {
        return INPUT_INVALID_FORMAT;
    }

    // Check for range
    if (value < min_val || value > max_val) {
        return INPUT_OUT_OF_RANGE;
    }

    *result = (int)value;
    return INPUT_VALID;
}

// Safe string copying
bool safe_string_copy(char* dest, const char* src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }

    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        return false;  // Not enough space
    }

    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';  // Ensure null termination
    return true;
}

// Clear input buffer safely
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Consume characters until newline or EOF
    }
}

// Print descriptive validation errors
void print_validation_error(InputValidationResult error, const char* parameter_name) {
    switch (error) {
        case INPUT_INVALID_FORMAT:
            printf("Error: Invalid format for %s. Please enter a numeric value.\n", parameter_name);
            break;
        case INPUT_OUT_OF_RANGE:
            printf("Error: %s value is out of acceptable range.\n", parameter_name);
            break;
        case INPUT_TOO_LONG:
            printf("Error: Input too long for %s. Maximum %d characters.\n", parameter_name, MAX_INPUT_LENGTH - 1);
            break;
        case INPUT_EMPTY:
            printf("Error: Empty input for %s. Please enter a value.\n", parameter_name);
            break;
        case INPUT_OVERFLOW:
            printf("Error: %s value causes overflow. Please enter a smaller number.\n", parameter_name);
            break;
        default:
            printf("Error: Unknown validation error for %s.\n", parameter_name);
            break;
    }
}

/*
 * SAFETY VALIDATOR REFERENCE SOLUTION NOTES:
 *
 * 1. MEMORY SAFETY TECHNIQUES:
 *    - Use fgets() instead of scanf() for string input
 *    - Always check buffer bounds before writing
 *    - Use strncpy() with explicit null termination
 *    - Validate all pointer parameters before use
 *    - Check array bounds before accessing elements
 *
 * 2. INPUT VALIDATION STRATEGIES:
 *    - Use strtof()/strtol() for safe numeric conversion
 *    - Check errno for overflow/underflow conditions
 *    - Validate that entire string was consumed
 *    - Implement comprehensive range checking
 *    - Handle empty and malformed inputs gracefully
 *
 * 3. ERROR HANDLING BEST PRACTICES:
 *    - Define clear error codes and messages
 *    - Provide specific feedback for each error type
 *    - Never crash on invalid input
 *    - Always validate function parameters
 *    - Use defensive programming techniques
 *
 * 4. DEFENSIVE PROGRAMMING:
 *    - Check for null pointers before dereferencing
 *    - Validate array indices before access
 *    - Use safety margins for critical parameters
 *    - Implement overflow checking for calculations
 *    - Provide fallback behavior for edge cases
 *
 * 5. ROBUST DESIGN PRINCIPLES:
 *    - Fail gracefully on invalid inputs
 *    - Provide clear error messages to users
 *    - Implement comprehensive bounds checking
 *    - Use safe string handling functions
 *    - Validate all external inputs thoroughly
 *
 * 6. TESTING CONSIDERATIONS:
 *    - Test with boundary values
 *    - Test with invalid inputs (letters, symbols)
 *    - Test with very large and very small numbers
 *    - Test with empty inputs and edge cases
 *    - Test buffer overflow conditions
 *
 * COMPILATION RECOMMENDATIONS:
 * gcc -Wall -Wextra -Werror -std=c11 -g -O2 -D_FORTIFY_SOURCE=2 \
 *     -fstack-protector-strong -Iinclude -o safety_validator \
 *     reference-solution/src/safety_validator.c
 *
 * SECURITY FEATURES IMPLEMENTED:
 * - Buffer overflow protection
 * - Input validation and sanitization
 * - Safe string handling
 * - Bounds checking for all arrays
 * - Overflow detection for numeric operations
 * - Graceful error handling and recovery
 */

