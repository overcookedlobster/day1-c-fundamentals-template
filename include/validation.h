/*
 * validation.h - Common validation functions and definitions
 * Day 1: C Fundamentals and Compilation Lab
 *
 * This header file provides common definitions and function prototypes
 * used across all Day 1 validation programs.
 *
 * Learning Objectives:
 * - Understand header file organization and include guards
 * - Practice using #define for constants
 * - Learn function prototype declarations
 */

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// TODO 1: Define common validation constants
// Hint: These constants are used across multiple programs

// Voltage specifications
#define NOMINAL_VOLTAGE_1V8     1.8f    // 1.8V power rail
#define NOMINAL_VOLTAGE_3V3     3.3f    // 3.3V power rail
#define VOLTAGE_TOLERANCE       5.0f    // ±5% tolerance

// Power specifications
#define MAX_POWER_BUDGET        2.0f    // Maximum power consumption (W)
#define THERMAL_LIMIT           85.0f   // Maximum temperature (°C)

// Current specifications
#define MIN_OPERATING_CURRENT   0.1f    // Minimum current (A)
#define MAX_OPERATING_CURRENT   1.5f    // Maximum current (A)

// Status codes
#define VALIDATION_PASS         0
#define VALIDATION_FAIL         1
#define VALIDATION_ERROR        -1

// TODO 2: Define validation result structure
// Hint: This structure can hold results from validation tests
typedef struct {
    float measured_value;
    float expected_value;
    float tolerance;
    bool is_valid;
    char status_message[100];
} ValidationResult;

// TODO 3: Function prototypes for common validation operations
// Hint: These functions can be implemented in separate .c files

/**
 * Validate if a voltage reading is within acceptable range
 * @param voltage: Measured voltage value
 * @param nominal: Expected nominal voltage
 * @param tolerance_percent: Acceptable tolerance percentage
 * @return: ValidationResult structure with test results
 */
ValidationResult validate_voltage(float voltage, float nominal, float tolerance_percent);

/**
 * Calculate power consumption from voltage and current
 * @param voltage: Voltage in volts
 * @param current: Current in amperes
 * @return: Power consumption in watts
 */
float calculate_power(float voltage, float current);

/**
 * Check if power consumption is within acceptable limits
 * @param power: Calculated power consumption
 * @param max_power: Maximum allowable power
 * @return: true if within limits, false otherwise
 */
bool is_power_acceptable(float power, float max_power);

/**
 * Format validation results for display
 * @param result: ValidationResult structure
 * @param buffer: Output buffer for formatted string
 * @param buffer_size: Size of output buffer
 */
void format_validation_result(const ValidationResult* result, char* buffer, size_t buffer_size);

/**
 * Calculate percentage difference between measured and expected values
 * @param measured: Measured value
 * @param expected: Expected value
 * @return: Percentage difference
 */
float calculate_percentage_error(float measured, float expected);

// TODO 4: Utility macros for common operations
// Hint: These macros can simplify repetitive calculations

// Calculate minimum value with tolerance
#define MIN_WITH_TOLERANCE(nominal, tolerance_percent) \
    ((nominal) * (1.0f - (tolerance_percent) / 100.0f))

// Calculate maximum value with tolerance
#define MAX_WITH_TOLERANCE(nominal, tolerance_percent) \
    ((nominal) * (1.0f + (tolerance_percent) / 100.0f))

// Check if value is within range
#define IS_IN_RANGE(value, min_val, max_val) \
    ((value) >= (min_val) && (value) <= (max_val))

// Convert percentage to decimal
#define PERCENT_TO_DECIMAL(percent) ((percent) / 100.0f)

// Round to specified decimal places
#define ROUND_TO_PLACES(value, places) \
    (roundf((value) * powf(10.0f, (places))) / powf(10.0f, (places)))

// TODO 5: Debug and logging macros
// Hint: These help with debugging and can be enabled/disabled

#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        printf("[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define VALIDATION_LOG(fmt, ...) \
        printf("[VALIDATION] " fmt "\n", ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
    #define VALIDATION_LOG(fmt, ...)
#endif

// Error handling macros
#define VALIDATION_ERROR_PRINT(fmt, ...) \
    fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__)

#define VALIDATION_WARNING_PRINT(fmt, ...) \
    printf("[WARNING] " fmt "\n", ##__VA_ARGS__)

// TODO 6: Input validation helper macros
// Hint: These can be used to validate user input

#define VALIDATE_INPUT_RANGE(value, min_val, max_val, var_name) \
    do { \
        if ((value) < (min_val) || (value) > (max_val)) { \
            VALIDATION_ERROR_PRINT("%s %.2f is out of range [%.2f, %.2f]", \
                                 (var_name), (value), (min_val), (max_val)); \
            return VALIDATION_ERROR; \
        } \
    } while(0)

#define VALIDATE_POSITIVE(value, var_name) \
    do { \
        if ((value) <= 0.0f) { \
            VALIDATION_ERROR_PRINT("%s %.2f must be positive", (var_name), (value)); \
            return VALIDATION_ERROR; \
        } \
    } while(0)

// TODO 7: Color output macros (for enhanced user experience)
// Hint: These add color to terminal output on supported systems

#define COLOR_RESET     "\033[0m"
#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_BLUE      "\033[34m"
#define COLOR_MAGENTA   "\033[35m"
#define COLOR_CYAN      "\033[36m"

#define PRINT_PASS(fmt, ...) \
    printf(COLOR_GREEN "✓ PASS: " fmt COLOR_RESET "\n", ##__VA_ARGS__)

#define PRINT_FAIL(fmt, ...) \
    printf(COLOR_RED "✗ FAIL: " fmt COLOR_RESET "\n", ##__VA_ARGS__)

#define PRINT_WARNING(fmt, ...) \
    printf(COLOR_YELLOW "⚠ WARNING: " fmt COLOR_RESET "\n", ##__VA_ARGS__)

#define PRINT_INFO(fmt, ...) \
    printf(COLOR_CYAN "ℹ INFO: " fmt COLOR_RESET "\n", ##__VA_ARGS__)

// TODO 8: Statistical analysis structures and functions
// Hint: These are useful for batch processing and analysis

typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
    float pass_rate;
    float average_value;
    float min_value;
    float max_value;
    float standard_deviation;
} ValidationStatistics;

/**
 * Initialize validation statistics structure
 * @param stats: Pointer to statistics structure
 */
void init_validation_stats(ValidationStatistics* stats);

/**
 * Update statistics with new test result
 * @param stats: Pointer to statistics structure
 * @param value: New measurement value
 * @param passed: Whether the test passed
 */
void update_validation_stats(ValidationStatistics* stats, float value, bool passed);

/**
 * Calculate final statistics (averages, standard deviation, etc.)
 * @param stats: Pointer to statistics structure
 */
void finalize_validation_stats(ValidationStatistics* stats);

/**
 * Print formatted statistics report
 * @param stats: Pointer to statistics structure
 * @param title: Title for the report
 */
void print_validation_stats(const ValidationStatistics* stats, const char* title);

#endif // VALIDATION_H

/*
 * HEADER FILE DESIGN NOTES:
 *
 * 1. Include Guards:
 *    - Prevent multiple inclusions of the same header
 *    - Use #ifndef/#define/#endif pattern
 *    - Header guard name should be unique (VALIDATION_H)
 *
 * 2. Constant Definitions:
 *    - Use #define for compile-time constants
 *    - Group related constants together
 *    - Use descriptive names with appropriate prefixes
 *
 * 3. Function Prototypes:
 *    - Declare functions that will be implemented elsewhere
 *    - Include parameter names for documentation
 *    - Use const qualifiers where appropriate
 *
 * 4. Macro Design:
 *    - Use macros for repetitive operations
 *    - Include do-while(0) pattern for multi-statement macros
 *    - Parenthesize macro parameters to avoid precedence issues
 *
 * 5. Documentation:
 *    - Include brief descriptions for all public functions
 *    - Document parameter meanings and return values
 *    - Provide usage examples where helpful
 *
 * USAGE EXAMPLES:
 *
 * // In your .c files:
 * #include "validation.h"
 *
 * // Use constants:
 * float min_voltage = MIN_WITH_TOLERANCE(NOMINAL_VOLTAGE_1V8, VOLTAGE_TOLERANCE);
 *
 * // Use validation functions:
 * ValidationResult result = validate_voltage(1.85f, NOMINAL_VOLTAGE_1V8, VOLTAGE_TOLERANCE);
 *
 * // Use debug macros:
 * DEBUG_PRINT("Testing voltage: %.2f", voltage_reading);
 */

