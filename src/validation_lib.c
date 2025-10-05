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
    ValidationResult result = {0};  // Initialize all fields to zero/default

    // Set basic fields for voltage test
    result.chip_variant_id = 0;
    strcpy(result.chip_name, "Test Chip");
    result.voltage = voltage;
    result.current = 0.0f;  // Default for power calc
    result.power = 0.0f;
    result.temperature = 25.0f;  // Nominal
    result.frequency = 500.0f;   // Nominal

    // Calculate acceptable voltage range
    float min_voltage = nominal * (1.0f - tolerance_percent / 100.0f);
    float max_voltage = nominal * (1.0f + tolerance_percent / 100.0f);

    // Set validation flags
    result.voltage_pass = (voltage >= min_voltage && voltage <= max_voltage);
    result.current_pass = true;   // Default pass for test
    result.power_pass = true;
    result.temperature_pass = true;
    result.frequency_pass = true;

    // Overall results
    int passed_count = result.voltage_pass + result.current_pass + result.power_pass +
                       result.temperature_pass + result.frequency_pass;
    result.overall_score = (passed_count / 5.0f) * 100.0f;
    result.overall_pass = (result.overall_score >= 80.0f);

    return result;
}

// Calculate power consumption from voltage and current
float calculate_power(float voltage, float current) {
    // Power (P) = Voltage (V) × Current (I)
    return voltage * current;
}

// Check if power consumption is within acceptable limits
bool is_power_acceptable(float power, float max_power) {
    // Implement power acceptability check
    return power <= max_power;
}

// Format validation results for display
void format_validation_result(const ValidationResult* result, char* buffer, size_t buffer_size) {
    if (result == NULL || buffer == NULL || buffer_size < 256) {
        return;
    }

    // Format using voltage and voltage_pass for basic tests
    snprintf(buffer, buffer_size,
            "Voltage: %.3fV - %s (Overall: %.1f%% %s)",
            result->voltage,
            result->voltage_pass ? "PASS" : "FAIL",
            result->overall_score,
            result->overall_pass ? "PASS" : "FAIL");
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

