/*
 * Day 1 Task 6: Multi-Parameter Validator - REFERENCE SOLUTION
 * Chip Parameter Validation System (Homework Extension)
 *
 * Learning Objectives:
 * - Read chip specifications from configuration files
 * - Validate multiple parameters simultaneously
 * - Generate detailed validation reports
 * - Support multiple chip configurations
 *
 * Real-World Context:
 * Production validation systems must check multiple parameters
 * simultaneously and generate comprehensive reports for quality
 * assurance and manufacturing process control.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/validation.h"

// Multi-parameter validation constants
#define MAX_LINE_LENGTH 256
#define MAX_CHIP_VARIANTS 10
#define MAX_PARAMETERS 20
#define CONFIG_FILE "config/chip_specs.txt"

// Chip variant structure
typedef struct {
    char name[64];
    float nominal_voltage;
    float max_current;
    float max_power;
    float max_temperature;
    float min_frequency;
    float max_frequency;
} ChipVariant;

// Parameter validation result
typedef struct {
    char parameter_name[32];
    float measured_value;
    float expected_value;
    float tolerance;
    bool is_valid;
    float deviation_percent;
} ParameterResult;

// Multi-parameter test result
typedef struct {
    int chip_variant_id;
    char chip_name[64];
    ParameterResult voltage_result;
    ParameterResult current_result;
    ParameterResult power_result;
    ParameterResult temperature_result;
    ParameterResult frequency_result;
    int total_parameters;
    int passed_parameters;
    float overall_score;
    bool chip_passes;
} MultiValidationResult;

// Global chip variants array
ChipVariant chip_variants[MAX_CHIP_VARIANTS];
int num_variants = 0;

// Function prototypes
bool load_chip_specifications(const char* filename);
void print_chip_variants(void);
int select_chip_variant(void);
bool validate_parameter(const char* param_name, float measured, float expected,
                       float tolerance, ParameterResult* result);
bool perform_multi_validation(int variant_id, MultiValidationResult* result);
void print_validation_report(const MultiValidationResult* result);
void generate_summary_report(MultiValidationResult* results, int num_tests);
float safe_read_float(const char* prompt, float min_val, float max_val);

int main() {
    printf("=== Multi-Parameter Chip Validator ===\n");
    printf("Advanced validation system for comprehensive chip testing.\n\n");

    // Load chip specifications from configuration file
    if (!load_chip_specifications(CONFIG_FILE)) {
        printf("Error: Could not load chip specifications from %s\n", CONFIG_FILE);
        printf("Using default specifications...\n\n");

        // Set up default chip variant
        strcpy(chip_variants[0].name, "Default Chip");
        chip_variants[0].nominal_voltage = 1.8f;
        chip_variants[0].max_current = 1.0f;
        chip_variants[0].max_power = 1.8f;
        chip_variants[0].max_temperature = 85.0f;
        chip_variants[0].min_frequency = 100.0f;
        chip_variants[0].max_frequency = 1000.0f;
        num_variants = 1;
    }

    printf("Loaded %d chip variant(s) for testing.\n\n", num_variants);

    // Array to store test results
    MultiValidationResult test_results[100];
    int num_tests = 0;

    bool continue_testing = true;
    while (continue_testing && num_tests < 100) {
        printf("--- Multi-Parameter Test #%d ---\n", num_tests + 1);

        // Display available chip variants
        print_chip_variants();

        // Select chip variant
        int variant_id = select_chip_variant();
        if (variant_id < 0 || variant_id >= num_variants) {
            printf("Invalid variant selection. Using variant 0.\n");
            variant_id = 0;
        }

        // Perform multi-parameter validation
        if (perform_multi_validation(variant_id, &test_results[num_tests])) {
            // Print individual test report
            print_validation_report(&test_results[num_tests]);
            num_tests++;
        } else {
            printf("Validation failed. Skipping this test.\n");
        }

        // Ask to continue
        char choice;
        printf("\nPerform another validation? (y/n): ");
        if (scanf(" %c", &choice) == 1) {
            continue_testing = (choice == 'y' || choice == 'Y');
        } else {
            continue_testing = false;
        }
        printf("\n");
    }

    // Generate comprehensive summary report
    if (num_tests > 0) {
        generate_summary_report(test_results, num_tests);
    } else {
        printf("No tests performed.\n");
    }

    printf("Multi-parameter validation completed.\n");
    return 0;
}

// Load chip specifications from configuration file
bool load_chip_specifications(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }

    char line[MAX_LINE_LENGTH];
    int current_variant = -1;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;

        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\0') {
            continue;
        }

        // Check for chip variant section
        if (strstr(line, "[CHIP_VARIANT_") != NULL) {
            current_variant++;
            if (current_variant >= MAX_CHIP_VARIANTS) {
                break;
            }

            // Extract variant name
            char* name_start = strchr(line, '_');
            if (name_start != NULL) {
                name_start += 9; // Skip "_VARIANT_"
                char* name_end = strchr(name_start, ']');
                if (name_end != NULL) {
                    *name_end = '\0';
                    snprintf(chip_variants[current_variant].name,
                            sizeof(chip_variants[current_variant].name),
                            "Chip Variant %s", name_start);
                }
            }
            continue;
        }

        // Parse parameter values
        if (current_variant >= 0) {
            char param[64], value_str[64];
            if (sscanf(line, "%63[^=]=%63s", param, value_str) == 2) {
                float value = atof(value_str);

                if (strcmp(param, "voltage") == 0) {
                    chip_variants[current_variant].nominal_voltage = value;
                } else if (strcmp(param, "max_current") == 0) {
                    chip_variants[current_variant].max_current = value;
                } else if (strcmp(param, "max_power") == 0) {
                    chip_variants[current_variant].max_power = value;
                } else if (strcmp(param, "max_temp") == 0) {
                    chip_variants[current_variant].max_temperature = value;
                } else if (strcmp(param, "frequency") == 0) {
                    chip_variants[current_variant].min_frequency = value * 0.8f;
                    chip_variants[current_variant].max_frequency = value * 1.2f;
                }
            }
        }
    }

    fclose(file);
    num_variants = current_variant + 1;
    return num_variants > 0;
}

// Print available chip variants
void print_chip_variants(void) {
    printf("Available chip variants:\n");
    for (int i = 0; i < num_variants; i++) {
        printf("  %d. %s\n", i, chip_variants[i].name);
        printf("     Voltage: %.1fV, Max Current: %.1fA, Max Power: %.1fW\n",
               chip_variants[i].nominal_voltage,
               chip_variants[i].max_current,
               chip_variants[i].max_power);
    }
    printf("\n");
}

// Select chip variant for testing
int select_chip_variant(void) {
    int selection;
    printf("Select chip variant (0-%d): ", num_variants - 1);
    if (scanf("%d", &selection) != 1) {
        return 0; // Default to first variant
    }
    return selection;
}

// Validate a single parameter
bool validate_parameter(const char* param_name, float measured, float expected,
                       float tolerance, ParameterResult* result) {
    if (result == NULL) {
        return false;
    }

    strcpy(result->parameter_name, param_name);
    result->measured_value = measured;
    result->expected_value = expected;
    result->tolerance = tolerance;

    // Calculate deviation percentage
    if (expected != 0.0f) {
        result->deviation_percent = ((measured - expected) / expected) * 100.0f;
    } else {
        result->deviation_percent = 0.0f;
    }

    // Check if within tolerance
    float min_acceptable = expected * (1.0f - tolerance / 100.0f);
    float max_acceptable = expected * (1.0f + tolerance / 100.0f);
    result->is_valid = (measured >= min_acceptable && measured <= max_acceptable);

    return true;
}

// Perform comprehensive multi-parameter validation
bool perform_multi_validation(int variant_id, MultiValidationResult* result) {
    if (result == NULL || variant_id < 0 || variant_id >= num_variants) {
        return false;
    }

    ChipVariant* variant = &chip_variants[variant_id];

    // Initialize result structure
    result->chip_variant_id = variant_id;
    strcpy(result->chip_name, variant->name);
    result->total_parameters = 5;
    result->passed_parameters = 0;

    printf("\nTesting %s:\n", variant->name);

    // Get voltage measurement
    float voltage = safe_read_float("Enter measured voltage (V): ", 0.0f, 5.0f);
    validate_parameter("Voltage", voltage, variant->nominal_voltage, 5.0f, &result->voltage_result);
    if (result->voltage_result.is_valid) result->passed_parameters++;

    // Get current measurement
    float current = safe_read_float("Enter measured current (A): ", 0.0f, 3.0f);
    validate_parameter("Current", current, variant->max_current * 0.8f, 10.0f, &result->current_result);
    if (result->current_result.is_valid) result->passed_parameters++;

    // Calculate and validate power
    float power = voltage * current;
    validate_parameter("Power", power, variant->max_power * 0.7f, 15.0f, &result->power_result);
    if (result->power_result.is_valid) result->passed_parameters++;

    // Get temperature measurement
    float temperature = safe_read_float("Enter measured temperature (°C): ", -50.0f, 150.0f);
    validate_parameter("Temperature", temperature, 25.0f, 20.0f, &result->temperature_result);
    if (result->temperature_result.is_valid) result->passed_parameters++;

    // Get frequency measurement
    float frequency = safe_read_float("Enter measured frequency (MHz): ", 0.0f, 2000.0f);
    float expected_freq = (variant->min_frequency + variant->max_frequency) / 2.0f;
    validate_parameter("Frequency", frequency, expected_freq, 10.0f, &result->frequency_result);
    if (result->frequency_result.is_valid) result->passed_parameters++;

    // Calculate overall score
    result->overall_score = ((float)result->passed_parameters / result->total_parameters) * 100.0f;
    result->chip_passes = (result->overall_score >= 80.0f);

    return true;
}

// Print detailed validation report
void print_validation_report(const MultiValidationResult* result) {
    if (result == NULL) {
        return;
    }

    printf("\n=== Validation Report: %s ===\n", result->chip_name);

    ParameterResult params[] = {
        result->voltage_result,
        result->current_result,
        result->power_result,
        result->temperature_result,
        result->frequency_result
    };

    printf("Parameter Analysis:\n");
    for (int i = 0; i < 5; i++) {
        printf("  %s: %.3f (expected: %.3f ±%.1f%%) %s\n",
               params[i].parameter_name,
               params[i].measured_value,
               params[i].expected_value,
               params[i].tolerance,
               params[i].is_valid ? "✓ PASS" : "✗ FAIL");

        if (!params[i].is_valid) {
            printf("    Deviation: %.1f%% (outside tolerance)\n", params[i].deviation_percent);
        }
    }

    printf("\nSummary:\n");
    printf("  Parameters passed: %d/%d\n", result->passed_parameters, result->total_parameters);
    printf("  Overall score: %.1f%%\n", result->overall_score);
    printf("  Chip status: %s\n", result->chip_passes ? "✓ PASS" : "✗ FAIL");

    if (result->chip_passes) {
        printf("  Quality grade: ");
        if (result->overall_score >= 95.0f) {
            printf("EXCELLENT\n");
        } else if (result->overall_score >= 90.0f) {
            printf("GOOD\n");
        } else {
            printf("ACCEPTABLE\n");
        }
    } else {
        printf("  Recommendation: REJECT - Parameters outside specifications\n");
    }
}

// Generate comprehensive summary report
void generate_summary_report(MultiValidationResult* results, int num_tests) {
    printf("\n=== Multi-Parameter Validation Summary ===\n");
    printf("Total tests performed: %d\n", num_tests);

    int passed_chips = 0;
    float total_score = 0.0f;
    int param_pass_counts[5] = {0}; // voltage, current, power, temp, freq

    for (int i = 0; i < num_tests; i++) {
        if (results[i].chip_passes) {
            passed_chips++;
        }
        total_score += results[i].overall_score;

        // Count individual parameter passes
        if (results[i].voltage_result.is_valid) param_pass_counts[0]++;
        if (results[i].current_result.is_valid) param_pass_counts[1]++;
        if (results[i].power_result.is_valid) param_pass_counts[2]++;
        if (results[i].temperature_result.is_valid) param_pass_counts[3]++;
        if (results[i].frequency_result.is_valid) param_pass_counts[4]++;
    }

    float pass_rate = ((float)passed_chips / num_tests) * 100.0f;
    float average_score = total_score / num_tests;

    printf("Chips passed: %d/%d (%.1f%%)\n", passed_chips, num_tests, pass_rate);
    printf("Average score: %.1f%%\n", average_score);

    printf("\nParameter-specific pass rates:\n");
    const char* param_names[] = {"Voltage", "Current", "Power", "Temperature", "Frequency"};
    for (int i = 0; i < 5; i++) {
        float param_rate = ((float)param_pass_counts[i] / num_tests) * 100.0f;
        printf("  %s: %d/%d (%.1f%%)\n", param_names[i], param_pass_counts[i], num_tests, param_rate);
    }

    printf("\nOverall Assessment: ");
    if (pass_rate >= 95.0f) {
        printf("✓ EXCELLENT - Manufacturing process is well controlled\n");
    } else if (pass_rate >= 85.0f) {
        printf("✓ GOOD - Manufacturing process is acceptable\n");
    } else if (pass_rate >= 70.0f) {
        printf("⚠ MARGINAL - Manufacturing process needs attention\n");
    } else {
        printf("✗ POOR - Manufacturing process requires immediate review\n");
    }
}

// Safe float input with validation
float safe_read_float(const char* prompt, float min_val, float max_val) {
    float value;
    int attempts = 0;
    const int max_attempts = 3;

    do {
        printf("%s", prompt);
        if (scanf("%f", &value) != 1) {
            printf("Error: Invalid input. Please enter a numeric value.\n");
            // Clear input buffer
            while (getchar() != '\n');
            attempts++;
            continue;
        }

        if (value < min_val || value > max_val) {
            printf("Error: Value %.3f is outside valid range [%.3f, %.3f]\n",
                   value, min_val, max_val);
            attempts++;
            continue;
        }

        return value;

    } while (attempts < max_attempts);

    printf("Too many invalid attempts. Using default value %.3f\n", min_val);
    return min_val;
}

/*
 * MULTI-PARAMETER VALIDATOR REFERENCE SOLUTION NOTES:
 *
 * 1. CONFIGURATION FILE HANDLING:
 *    - Parse chip specifications from external files
 *    - Support multiple chip variants
 *    - Handle missing or malformed configuration gracefully
 *    - Provide fallback default configurations
 *
 * 2. MULTI-PARAMETER VALIDATION:
 *    - Validate voltage, current, power, temperature, frequency
 *    - Calculate derived parameters (power from V×I)
 *    - Apply different tolerances for different parameters
 *    - Track individual parameter pass/fail status
 *
 * 3. COMPREHENSIVE REPORTING:
 *    - Individual test reports with detailed analysis
 *    - Parameter-specific deviation calculations
 *    - Overall chip pass/fail determination
 *    - Quality grading based on performance
 *    - Summary statistics across multiple tests
 *
 * 4. DATA STRUCTURES:
 *    - ChipVariant structure for specifications
 *    - ParameterResult for individual parameter validation
 *    - MultiValidationResult for comprehensive test results
 *    - Arrays for batch processing and statistics
 *
 * 5. USER INTERFACE:
 *    - Clear prompts and instructions
 *    - Variant selection menu
 *    - Input validation with retry logic
 *    - Formatted output with visual indicators
 *
 * 6. ERROR HANDLING:
 *    - Safe file operations with error checking
 *    - Input validation with range checking
 *    - Graceful degradation on errors
 *    - Default values for missing data
 *
 * 7. STATISTICAL ANALYSIS:
 *    - Pass rate calculations
 *    - Parameter-specific statistics
 *    - Average score computation
 *    - Manufacturing process assessment
 *
 * TESTING SCENARIOS:
 * - Test with different chip variants
 * - Test with parameters at specification limits
 * - Test with out-of-specification parameters
 * - Test with missing configuration file
 * - Test with invalid inputs
 * - Test batch processing with multiple chips
 *
 * EXTENSION OPPORTUNITIES:
 * - Export reports to CSV/JSON format
 * - Add graphical trending analysis
 * - Implement statistical process control
 * - Add temperature coefficient validation
 * - Support for custom parameter definitions
 * - Integration with automated test equipment
 */

