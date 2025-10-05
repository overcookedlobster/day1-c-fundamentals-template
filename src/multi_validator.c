/*
 * Day 1 Task 6: Multi-Parameter Validator - STUDENT TEMPLATE
 * Chip Parameter Validation System (Homework Extension)
 *
 * Learning Objectives:
 * - Read chip specifications from configuration files
 * - Validate multiple parameters simultaneously
 * - Generate detailed validation reports
 * - Support multiple chip configurations
 *
 * INSTRUCTIONS: Complete the TODOs to implement a comprehensive
 * multi-parameter validation system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/validation.h"

// TODO: Define constants for multi-parameter validation
#define MAX_LINE_LENGTH 256
#define MAX_CHIP_VARIANTS 10
#define CONFIG_FILE "config/chip_specs.txt"

// TODO: Define chip variant structure
typedef struct {
    char name[64];
    float nominal_voltage;
    float min_current;
    float max_current;
    float min_temperature;
    float max_temperature;
    float max_power;
    float min_frequency;
    float max_frequency;
} ChipVariant;


// Global variables
ChipVariant chip_variants[MAX_CHIP_VARIANTS];
int num_variants = 0;
float voltage_tolerance = 0.05f;

// TODO: Implement function to load chip specifications
bool load_chip_specifications(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Warning: Could not open %s. Using defaults.\n", filename);
        // Set default chip variant
        strcpy(chip_variants[0].name, "Standard Chip");
        chip_variants[0].nominal_voltage = 1.8f;
        chip_variants[0].min_current = 0.1f;
        chip_variants[0].max_current = 1.5f;
        chip_variants[0].min_temperature = -40.0f;
        chip_variants[0].max_temperature = 85.0f;
        chip_variants[0].max_power = 2.0f;
        chip_variants[0].min_frequency = 100.0f;
        chip_variants[0].max_frequency = 1000.0f;
        num_variants = 1;
        return false;
    }

    // Parse configuration file
    float nominal_1v8 = 0.0f;
    float nominal_3v3 = 0.0f;
    float min_curr = 0.1f;
    float max_curr = 1.5f;
    float max_pow = 2.0f;
    float min_temp = -40.0f;
    float max_temp = 85.0f;
    float min_freq = 100.0f;
    float max_freq = 1000.0f;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || strlen(line) < 2) continue;

        char *eq_pos = strchr(line, '=');
        if (!eq_pos) continue;

        *eq_pos = '\0';
        char *key = line;
        char *val_str = eq_pos + 1;

        // Trim leading spaces from value
        while (*val_str == ' ') val_str++;

        // Trim trailing spaces and newline
        char *end = val_str + strlen(val_str) - 1;
        while (end > val_str && (*end == ' ' || *end == '\n' || *end == '\r')) {
            *end-- = '\0';
            end--;
        }

        float val = atof(val_str);

        if (strcmp(key, "nominal_voltage_1v8") == 0) {
            nominal_1v8 = val;
        } else if (strcmp(key, "nominal_voltage_3v3") == 0) {
            nominal_3v3 = val;
        } else if (strcmp(key, "min_operating_current") == 0) {
            min_curr = val;
        } else if (strcmp(key, "max_operating_current") == 0) {
            max_curr = val;
        } else if (strcmp(key, "max_power_budget") == 0) {
            max_pow = val;
        } else if (strcmp(key, "min_operating_temperature") == 0) {
            min_temp = val;
        } else if (strcmp(key, "max_operating_temperature") == 0) {
            max_temp = val;
        } else if (strcmp(key, "min_frequency") == 0) {
            min_freq = val;
        } else if (strcmp(key, "max_frequency") == 0) {
            max_freq = val;
        } else if (strcmp(key, "voltage_tolerance_percent") == 0) {
            voltage_tolerance = val / 100.0f;
        }
    }

    fclose(file);

    num_variants = 0;

    // Create 1.8V variant if specified
    if (nominal_1v8 > 0.0f) {
        strcpy(chip_variants[num_variants].name, "1.8V Chip");
        chip_variants[num_variants].nominal_voltage = nominal_1v8;
        chip_variants[num_variants].min_current = min_curr;
        chip_variants[num_variants].max_current = max_curr;
        chip_variants[num_variants].min_temperature = min_temp;
        chip_variants[num_variants].max_temperature = max_temp;
        chip_variants[num_variants].max_power = max_pow;
        chip_variants[num_variants].min_frequency = min_freq;
        chip_variants[num_variants].max_frequency = max_freq;
        num_variants++;
    }

    // Create 3.3V variant if specified
    if (nominal_3v3 > 0.0f) {
        strcpy(chip_variants[num_variants].name, "3.3V Chip");
        chip_variants[num_variants].nominal_voltage = nominal_3v3;
        chip_variants[num_variants].min_current = min_curr;
        chip_variants[num_variants].max_current = max_curr;
        chip_variants[num_variants].min_temperature = min_temp;
        chip_variants[num_variants].max_temperature = max_temp;
        chip_variants[num_variants].max_power = max_pow;
        chip_variants[num_variants].min_frequency = min_freq;
        chip_variants[num_variants].max_frequency = max_freq;
        num_variants++;
    }

    // If no variants loaded, use default
    if (num_variants == 0) {
        strcpy(chip_variants[0].name, "Standard Chip");
        chip_variants[0].nominal_voltage = 1.8f;
        chip_variants[0].min_current = 0.1f;
        chip_variants[0].max_current = 1.5f;
        chip_variants[0].min_temperature = -40.0f;
        chip_variants[0].max_temperature = 85.0f;
        chip_variants[0].max_power = 2.0f;
        chip_variants[0].min_frequency = 100.0f;
        chip_variants[0].max_frequency = 1000.0f;
        num_variants = 1;
    }

    printf("Loaded %d chip variant(s).\n", num_variants);
    return true;
}

// TODO: Implement multi-parameter validation function
bool validate_multiple_parameters(int variant_id, ValidationResult* result) {
    if (variant_id < 0 || variant_id >= num_variants || result == NULL) {
        return false;
    }

    ChipVariant* variant = &chip_variants[variant_id];
    result->chip_variant_id = variant_id;
    strcpy(result->chip_name, variant->name);

    printf("\nTesting %s:\n", variant->name);

    // TODO: Get input for all parameters
    printf("Enter voltage (V): ");
    if (scanf("%f", &result->voltage) != 1) {
        printf("Invalid input\n");
        return false;
    }

    printf("Enter current (A): ");
    if (scanf("%f", &result->current) != 1) {
        printf("Invalid input\n");
        return false;
    }

    printf("Enter temperature (°C): ");
    if (scanf("%f", &result->temperature) != 1) {
        printf("Invalid input\n");
        return false;
    }

    printf("Enter frequency (MHz): ");
    if (scanf("%f", &result->frequency) != 1) {
        printf("Invalid input\n");
        return false;
    }

    // TODO: Calculate derived parameters
    result->power = result->voltage * result->current;

    // TODO: Validate each parameter
    result->voltage_pass = (result->voltage >= variant->nominal_voltage * (1.0f - voltage_tolerance)) &&
                          (result->voltage <= variant->nominal_voltage * (1.0f + voltage_tolerance));

    result->current_pass = (result->current >= variant->min_current) &&
                          (result->current <= variant->max_current);

    result->power_pass = (result->power <= variant->max_power);

    result->temperature_pass = (result->temperature >= variant->min_temperature) &&
                              (result->temperature <= variant->max_temperature);

    result->frequency_pass = (result->frequency >= variant->min_frequency) &&
                            (result->frequency <= variant->max_frequency);

    // TODO: Calculate overall result
    int passed_params = 0;
    if (result->voltage_pass) passed_params++;
    if (result->current_pass) passed_params++;
    if (result->power_pass) passed_params++;
    if (result->temperature_pass) passed_params++;
    if (result->frequency_pass) passed_params++;

    result->overall_score = (passed_params / 5.0f) * 100.0f;
    result->overall_pass = (result->overall_score >= 80.0f);

    return true;
}

// TODO: Implement report generation function
void generate_validation_report(const ValidationResult* result) {
    if (result == NULL) {
        return;
    }

    printf("\n=== Validation Report: %s ===\n", result->chip_name);
    printf("Voltage: %.2fV %s\n", result->voltage, result->voltage_pass ? "PASS" : "FAIL");
    printf("Current: %.2fA %s\n", result->current, result->current_pass ? "PASS" : "FAIL");
    printf("Power: %.2fW %s\n", result->power, result->power_pass ? "PASS" : "FAIL");
    printf("Temperature: %.1f°C %s\n", result->temperature, result->temperature_pass ? "PASS" : "FAIL");
    printf("Frequency: %.0fMHz %s\n", result->frequency, result->frequency_pass ? "PASS" : "FAIL");
    printf("Overall Score: %.1f%%\n", result->overall_score);
    printf("Overall Result: %s\n", result->overall_pass ? "✓ PASS" : "✗ FAIL");
}

int main() {
    printf("=== Multi-Parameter Chip Validator ===\n");
    printf("Advanced validation system for comprehensive chip testing.\n\n");

    // TODO: Load chip specifications
    if (!load_chip_specifications(CONFIG_FILE)) {
        printf("Using default chip specifications.\n");
    }

    // TODO: Display available chip variants
    printf("Available chip variants:\n");
    for (int i = 0; i < num_variants; i++) {
        printf("  %d. %s\n", i, chip_variants[i].name);
    }

    // TODO: Select chip variant
    int variant_id = 0;
    printf("\nSelect chip variant (0-%d): ", num_variants - 1);
    if (scanf("%d", &variant_id) != 1 || variant_id < 0 || variant_id >= num_variants) {
        printf("Invalid selection. Using variant 0.\n");
        variant_id = 0;
    }

    // TODO: Perform validation tests
    ValidationResult results[10];
    int num_tests = 0;
    bool continue_testing = true;

    while (continue_testing && num_tests < 10) {
        printf("\n--- Test #%d ---\n", num_tests + 1);

        if (validate_multiple_parameters(variant_id, &results[num_tests])) {
            generate_validation_report(&results[num_tests]);
            num_tests++;
        } else {
            printf("Validation failed. Skipping this test.\n");
        }

        // TODO: Ask to continue
        char choice;
        printf("\nPerform another test? (y/n): ");
        if (scanf(" %c", &choice) == 1) {
            continue_testing = (choice == 'y' || choice == 'Y');
        } else {
            continue_testing = false;
        }
    }

    // TODO: Generate summary report
    if (num_tests > 0) {
        printf("\n=== Summary Report ===\n");
        printf("Total tests: %d\n", num_tests);

        int passed_tests = 0;
        float total_score = 0.0f;

        for (int i = 0; i < num_tests; i++) {
            if (results[i].overall_pass) {
                passed_tests++;
            }
            total_score += results[i].overall_score;
        }

        float pass_rate = ((float)passed_tests / num_tests) * 100.0f;
        float average_score = total_score / num_tests;

        printf("Passed: %d/%d (%.1f%%)\n", passed_tests, num_tests, pass_rate);
        printf("Average score: %.1f%%\n", average_score);

        if (pass_rate >= 90.0f) {
            printf("Quality Assessment: ✓ EXCELLENT\n");
        } else if (pass_rate >= 70.0f) {
            printf("Quality Assessment: ⚠ ACCEPTABLE\n");
        } else {
            printf("Quality Assessment: ✗ POOR\n");
        }
    }

    printf("\nMulti-parameter validation completed.\n");
    return 0;
}

/*
 * MULTI-PARAMETER VALIDATOR TEMPLATE NOTES:
 *
 * Students should enhance this template by:
 *
 * 1. CONFIGURATION FILE PARSING:
 *    - Implement proper file parsing for chip specifications
 *    - Handle different chip variants and their parameters
 *    - Add error handling for malformed configuration files
 *    - Support comments and different file formats
 *
 * 2. ENHANCED VALIDATION:
 *    - Add more sophisticated validation rules
 *    - Implement parameter interdependencies
 *    - Add statistical analysis of results
 *    - Support different tolerance levels
 *
 * 3. REPORTING IMPROVEMENTS:
 *    - Generate detailed HTML or CSV reports
 *    - Add graphical result visualization
 *    - Include historical trend analysis
 *    - Export results to external systems
 *
 * 4. USER INTERFACE:
 *    - Add menu-driven interface
 *    - Implement batch processing mode
 *    - Add configuration file editor
 *    - Support command-line arguments
 *
 * TESTING SCENARIOS:
 * - Test with different chip variants
 * - Test with parameters at specification limits
 * - Test with invalid configuration files
 * - Test batch processing with multiple chips
 *
 * COMPILATION:
 * gcc -Wall -Wextra -std=c11 -g -Iinclude -o multi_validator src/multi_validator.c
 */


