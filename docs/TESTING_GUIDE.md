# Testing Guide for Day 1 C Fundamentals

This guide provides comprehensive instructions for testing the Day 1 C Fundamentals assignment, including both automated testing and manual validation procedures.

## Overview

The testing framework consists of:
- **Unit Tests**: Automated tests for individual functions
- **Integration Tests**: End-to-end testing of complete programs
- **Reference Solutions**: Complete working implementations
- **Test Data**: Sample inputs and expected outputs
- **Validation Scripts**: Automated testing and grading tools

## Quick Start

### Running All Tests
```bash
# Run the complete test suite
make test

# Run tests with verbose output
./scripts/run_tests.sh --verbose

# Run only essential tests
./scripts/run_tests.sh --quick
```

### Testing Individual Components
```bash
# Test voltage validation functions
./tests/test_voltage

# Test power calculation functions
./tests/test_power

# Test reference solutions
cd reference-solution && make test
```

## Test Framework Structure

```
tests/
├── test_voltage.c          # Unit tests for voltage validation
├── test_power.c            # Unit tests for power calculations
├── expected_outputs/       # Expected program outputs
│   ├── voltage_checker_output.txt
│   └── power_calculator_output.txt
└── test_data/             # Sample input files
    ├── valid_inputs.txt
    └── invalid_inputs.txt
```

## Unit Tests

### Voltage Validation Tests (`test_voltage.c`)

Tests the following functionality:
- **Range Calculation**: Verify tolerance calculations (1.8V ±5%)
- **Valid Inputs**: Test voltages within acceptable range
- **Invalid Inputs**: Test voltages outside acceptable range
- **Boundary Conditions**: Test exact limits (1.71V, 1.89V)
- **Edge Cases**: Test zero, negative, and extreme values
- **Statistics**: Test validation statistics tracking
- **Macros**: Test utility macros and functions

**Sample Test Output:**
```
=== Voltage Validation Test Suite ===

Running test 1/10: Voltage Range Calculation
PASS: Voltage range calculation

Running test 2/10: Valid Voltage Readings
PASS: Valid voltage readings

...

=== Test Summary ===
Total tests: 10
Passed: 10
Failed: 0
Pass rate: 100.0%

✓ ALL TESTS PASSED!
```

### Power Calculation Tests (`test_power.c`)

Tests the following functionality:
- **Basic Calculations**: P = V × I calculations
- **Edge Cases**: Zero values, boundary conditions
- **Power Limits**: Validation against maximum power
- **Input Ranges**: Voltage and current range validation
- **Efficiency Categories**: Power efficiency classification
- **Statistics**: Multi-calculation statistics
- **Budget Utilization**: Power budget calculations

## Integration Tests

### Manual Testing Procedures

#### Voltage Checker Testing
```bash
# Compile the reference solution
cd reference-solution
make voltage_checker

# Test with valid inputs
echo -e "1.8\n1.75\n1.85\n-1" | ./voltage_checker

# Test with invalid inputs
echo -e "1.5\n2.0\n0.0\n-1" | ./voltage_checker

# Test boundary conditions
echo -e "1.71\n1.89\n1.70\n1.90\n-1" | ./voltage_checker
```

#### Power Calculator Testing
```bash
# Compile the reference solution
cd reference-solution
make power_calculator

# Test normal operation
echo -e "1.8\n0.5\nn" | ./power_calculator

# Test power limit violation
echo -e "1.8\n1.5\nn" | ./power_calculator

# Test input validation
echo -e "2.5\n1.8\n0.5\nn" | ./power_calculator
```

### Automated Integration Testing

The `run_tests.sh` script provides automated integration testing:

```bash
# Run with different options
./scripts/run_tests.sh                    # Standard test run
./scripts/run_tests.sh --verbose          # Detailed output
./scripts/run_tests.sh --clean            # Clean before testing
./scripts/run_tests.sh --quick            # Essential tests only
```

## Reference Solutions

The `reference-solution/` directory contains complete, working implementations of all programs:

### Available Programs
- `voltage_checker.c` - Complete voltage validation system
- `power_calculator.c` - Complete power calculation system
- `debug_practice.c` - Corrected version with all errors fixed
- `safety_validator.c` - Robust input validation system
- `multi_validator.c` - Multi-parameter validation system
- `batch_processor.c` - Batch processing system

### Testing Reference Solutions
```bash
cd reference-solution

# Build all reference programs
make all

# Test individual programs
./voltage_checker
./power_calculator
./safety_validator

# Run reference solution tests
make test
```

## Test Data and Configuration

### Configuration Files
- `config/chip_specs.txt` - Chip specifications for multi-parameter validation
- `config/test_cases.txt` - Test cases for batch processing

### Sample Test Cases
The test case file includes various scenarios:
- **Normal Operation**: Standard voltage/current combinations
- **Boundary Conditions**: Values at specification limits
- **Invalid Inputs**: Out-of-range parameters
- **Edge Cases**: Special conditions and error cases
- **Stress Tests**: Large datasets for performance testing

### Expected Outputs
Reference outputs are provided in `tests/expected_outputs/` for:
- Voltage checker with various inputs
- Power calculator with different scenarios
- Error handling demonstrations
- Statistical summary reports

## Compilation Mode Testing

Test different compilation modes:

```bash
# Demonstrate compilation differences
./scripts/compilation_demo.sh demo

# Test specific program with different modes
./scripts/compilation_demo.sh voltage_checker

# Show compilation flags
make show-flags
```

## Performance Testing

### Memory Usage Testing
```bash
# Compile with debugging symbols
make debug

# Run with valgrind (if available)
valgrind --leak-check=full ./reference-solution/voltage_checker

# Test with large datasets
./reference-solution/batch_processor -i large_test_set.txt
```

### Stress Testing
```bash
# Generate large test dataset
python3 -c "
for i in range(10000):
    print(f'TEST{i:05d}|Stress test {i}|{1.5 + i*0.0001}|{0.1 + i*0.00001}|{(1.5 + i*0.0001)*(0.1 + i*0.00001)}|PASS|STRESS')
" > large_test_set.txt

# Run batch processor
./reference-solution/batch_processor -i large_test_set.txt -o stress_results.csv
```

## Debugging and Troubleshooting

### Common Issues

#### Compilation Errors
```bash
# Check for missing dependencies
make clean
make all

# Verify include paths
gcc -Wall -Wextra -std=c11 -Iinclude -E src/voltage_checker.c | grep validation.h
```

#### Runtime Errors
```bash
# Enable debug output
export DEBUG=1
./voltage_checker

# Use GDB for debugging
gdb ./voltage_checker
(gdb) run
(gdb) bt
```

#### Test Failures
```bash
# Run individual test with verbose output
./tests/test_voltage 2>&1 | tee test_output.log

# Check test data integrity
head -20 config/test_cases.txt
```

### Debugging Tools

#### GCC Debugging Flags
```bash
# Compile with maximum debugging information
gcc -Wall -Wextra -g -O0 -DDEBUG -std=c11 -Iinclude -o debug_program src/program.c

# Enable all warnings
gcc -Wall -Wextra -Wpedantic -Wconversion -std=c11 -Iinclude -o program src/program.c
```

#### Static Analysis
```bash
# Use GCC static analyzer (if available)
gcc -fanalyzer -Wall -Wextra -std=c11 -Iinclude -o program src/program.c

# Use cppcheck (if available)
cppcheck --enable=all --std=c11 src/
```

## Grading and Assessment

### Automated Grading Criteria

The testing framework evaluates:

1. **Compilation (25 points)**
   - Programs compile without errors
   - No warnings with -Wall -Wextra
   - Proper use of C11 standard

2. **Functionality (40 points)**
   - Correct voltage validation logic
   - Accurate power calculations
   - Proper input/output handling
   - Error handling implementation

3. **Code Quality (20 points)**
   - Proper variable initialization
   - Appropriate data types
   - Clear function organization
   - Consistent coding style

4. **Testing (15 points)**
   - All unit tests pass
   - Integration tests successful
   - Handles edge cases correctly
   - Robust error handling

### Manual Review Checklist

- [ ] Code compiles without warnings
- [ ] Programs handle invalid input gracefully
- [ ] Output format matches specifications
- [ ] Mathematical calculations are correct
- [ ] Memory management is proper (no leaks)
- [ ] Code is well-commented and readable
- [ ] Error messages are informative
- [ ] Edge cases are handled appropriately

## Continuous Integration

### GitHub Actions Workflow

The repository includes automated testing via GitHub Actions:

```yaml
# .github/workflows/ci.yml
name: Day 1 C Fundamentals CI

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Install dependencies
      run: sudo apt-get update && sudo apt-get install -y gcc make
    - name: Run tests
      run: make test
    - name: Run integration tests
      run: ./scripts/run_tests.sh
```

### Local Pre-commit Testing

```bash
# Create pre-commit hook
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
echo "Running pre-commit tests..."
make test
if [ $? -ne 0 ]; then
    echo "Tests failed. Commit aborted."
    exit 1
fi
echo "All tests passed."
EOF

chmod +x .git/hooks/pre-commit
```

## Advanced Testing

### Fuzzing
```bash
# Generate random test inputs
python3 -c "
import random
for i in range(1000):
    voltage = random.uniform(-5.0, 10.0)
    current = random.uniform(-2.0, 5.0)
    print(f'{voltage:.3f}\\n{current:.3f}\\nn')
" | ./reference-solution/power_calculator
```

### Coverage Analysis
```bash
# Compile with coverage flags
gcc -Wall -Wextra -std=c11 -g --coverage -Iinclude -o test_coverage tests/test_voltage.c src/validation_lib.c -lm

# Run tests
./test_coverage

# Generate coverage report
gcov test_voltage.c
```

## Conclusion

This testing framework provides comprehensive validation of the Day 1 C Fundamentals assignment. It ensures that students learn proper C programming practices while building robust, well-tested validation systems for chip parameter testing.

For additional help or questions about testing procedures, refer to the course documentation or contact the teaching staff.

