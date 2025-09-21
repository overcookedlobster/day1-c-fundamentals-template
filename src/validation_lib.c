/*
 * validation_lib.c - Implementation of validation functions
 * Day 1: C Fundamentals and Compilation Lab
 *
 * This file implements the validation functions declared in validation.h
 * These functions are used by the test framework and can be used by
 * student implementations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/validation.h"

// Validate if a voltage reading is within acceptable range
ValidationResult validate_voltage(float voltage, float nominal, float tolerance_percent) {
    ValidationResult result;

    // TODO: Initialize the result structure with input values
    // Hint: Set measured_value, expected_value, and tolerance
    result.measured_value = 0.0f;       // TODO: Set to voltage parameter
    result.expected_value = 0.0f;       // TODO: Set to nominal parameter
    result.tolerance = 0.0f;            // TODO: Set to tolerance_percent parameter

    // TODO: Calculate acceptable voltage range
    // Hint: min_voltage = nominal * (1.0f - tolerance_percent / 100.0f)
    // Hint: max_voltage = nominal * (1.0f + tolerance_percent / 100.0f)
    float min_voltage = 0.0f;  // TODO: Calculate minimum acceptable voltage
    float max_voltage = 0.0f;  // TODO: Calculate maximum acceptable voltage

    // TODO: Check if voltage is within acceptable range
    // Hint: voltage should be >= min_voltage AND <= max_voltage
    result.is_valid = false;  // TODO: Implement validation logic

    // TODO: Generate appropriate status message
    // Hint: Use snprintf to create descriptive message based on is_valid
    snprintf(result.status_message, sizeof(result.status_message),
             "TODO: Implement status message");

    return result;
}

// Calculate power consumption from voltage and current
float calculate_power(float voltage, float current) {
    // TODO: Implement power calculation using Ohm's Law
    // Hint: Power (P) = Voltage (V) × Current (I)
    return 0.0f;  // TODO: Replace with actual calculation
}

// Check if power consumption is within acceptable limits
bool is_power_acceptable(float power, float max_power) {
    // TODO: Implement power acceptability check
    // Hint: Return true if power is less than or equal to max_power
    return false;  // TODO: Replace with actual logic
}

// Format validation results for display
void format_validation_result(const ValidationResult* result, char* buffer, size_t buffer_size) {
    if (result == NULL || buffer == NULL) {
        return;
    }

    snprintf(buffer, buffer_size,
            "Parameter: %.3f (expected: %.3f ±%.1f%%) - %s",
            result->measured_value,
            result->expected_value,
            result->tolerance,
            result->is_valid ? "PASS" : "FAIL");
}

// Calculate percentage difference between measured and expected values
float calculate_percentage_error(float measured, float expected) {
    if (expected == 0.0f) {
        return 0.0f;
    }

    return ((measured - expected) / expected) * 100.0f;
}

// Initialize validation statistics structure
void init_validation_stats(ValidationStatistics* stats) {
    if (stats == NULL) {
        return;
    }

    stats->total_tests = 0;
    stats->passed_tests = 0;
    stats->failed_tests = 0;
    stats->pass_rate = 0.0f;
    stats->average_value = 0.0f;
    stats->min_value = 0.0f;
    stats->max_value = 0.0f;
    stats->standard_deviation = 0.0f;
}

// Update statistics with new test result
void update_validation_stats(ValidationStatistics* stats, float value, bool passed) {
    if (stats == NULL) {
        return;
    }

    // Update counts
    stats->total_tests++;
    if (passed) {
        stats->passed_tests++;
    } else {
        stats->failed_tests++;
    }

    // Update value statistics
    if (stats->total_tests == 1) {
        stats->min_value = value;
        stats->max_value = value;
        stats->average_value = value;
    } else {
        if (value < stats->min_value) {
            stats->min_value = value;
        }
        if (value > stats->max_value) {
            stats->max_value = value;
        }

        // Update running average
        stats->average_value = ((stats->average_value * (stats->total_tests - 1)) + value) / stats->total_tests;
    }
}

// Calculate final statistics (averages, standard deviation, etc.)
void finalize_validation_stats(ValidationStatistics* stats) {
    if (stats == NULL || stats->total_tests == 0) {
        return;
    }

    // Calculate pass rate
    stats->pass_rate = ((float)stats->passed_tests / stats->total_tests) * 100.0f;

    // Note: Standard deviation calculation would require storing all values
    // For this implementation, we'll set it to 0 as a placeholder
    stats->standard_deviation = 0.0f;
}

// Print formatted statistics report
void print_validation_stats(const ValidationStatistics* stats, const char* title) {
    if (stats == NULL) {
        return;
    }

    printf("=== %s ===\n", title ? title : "Validation Statistics");
    printf("Total tests: %d\n", stats->total_tests);
    printf("Passed: %d\n", stats->passed_tests);
    printf("Failed: %d\n", stats->failed_tests);
    printf("Pass rate: %.1f%%\n", stats->pass_rate);

    if (stats->total_tests > 0) {
        printf("Average value: %.3f\n", stats->average_value);
        printf("Value range: %.3f - %.3f\n", stats->min_value, stats->max_value);
    }

    printf("========================\n");
}

