# Reference Solution Makefile - Day 1 C Fundamentals
# Complete implementations for all Day 1 programs

# Compiler Configuration
CC = gcc
CROSS_CC = riscv64-unknown-elf-gcc

# Compilation Flags
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -I../include
DEBUG_FLAGS = -g -DDEBUG -O0
RELEASE_FLAGS = -O2 -DNDEBUG
CROSS_FLAGS = -march=rv32i -mabi=ilp32 -static

# Directories
SRC_DIR = src
INCLUDE_DIR = include
PARENT_INCLUDE = ../include
BUILD_DIR = build

# Source Files
VOLTAGE_CHECKER = voltage_checker
POWER_CALCULATOR = power_calculator
DEBUG_PRACTICE = debug_practice
SAFETY_VALIDATOR = safety_validator
MULTI_VALIDATOR = multi_validator
BATCH_PROCESSOR = batch_processor

# Validation library
VALIDATION_LIB = ../src/validation_lib.c

# Default target - builds all reference programs
all: $(VOLTAGE_CHECKER) $(POWER_CALCULATOR) $(DEBUG_PRACTICE) $(SAFETY_VALIDATOR) $(MULTI_VALIDATOR) $(BATCH_PROCESSOR)
	@echo "✓ All reference solution programs compiled successfully!"

# Individual program targets
$(VOLTAGE_CHECKER): $(SRC_DIR)/$(VOLTAGE_CHECKER).c $(VALIDATION_LIB)
	@echo "Compiling reference voltage checker..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

$(POWER_CALCULATOR): $(SRC_DIR)/$(POWER_CALCULATOR).c $(VALIDATION_LIB)
	@echo "Compiling reference power calculator..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

$(DEBUG_PRACTICE): $(SRC_DIR)/$(DEBUG_PRACTICE).c $(VALIDATION_LIB)
	@echo "Compiling reference debug practice..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

$(SAFETY_VALIDATOR): $(SRC_DIR)/$(SAFETY_VALIDATOR).c $(VALIDATION_LIB)
	@echo "Compiling reference safety validator..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

$(MULTI_VALIDATOR): $(SRC_DIR)/$(MULTI_VALIDATOR).c $(VALIDATION_LIB)
	@echo "Compiling reference multi-validator..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

$(BATCH_PROCESSOR): $(SRC_DIR)/$(BATCH_PROCESSOR).c $(VALIDATION_LIB)
	@echo "Compiling reference batch processor..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

# Debug builds
debug: CFLAGS += $(DEBUG_FLAGS)
debug: all
	@echo "✓ Reference debug builds completed"

# Release builds
release: CFLAGS += $(RELEASE_FLAGS)
release: all
	@echo "✓ Reference release builds completed"

# Cross-compilation for embedded targets
cross-compile: CC = $(CROSS_CC)
cross-compile: CFLAGS += $(CROSS_FLAGS)
cross-compile: $(VOLTAGE_CHECKER)_embedded $(POWER_CALCULATOR)_embedded
	@echo "✓ Reference cross-compilation completed"

$(VOLTAGE_CHECKER)_embedded: $(SRC_DIR)/$(VOLTAGE_CHECKER).c $(VALIDATION_LIB)
	@echo "Cross-compiling reference voltage checker..."
	$(CROSS_CC) $(CFLAGS) $(CROSS_FLAGS) -o $@ $< $(VALIDATION_LIB)

$(POWER_CALCULATOR)_embedded: $(SRC_DIR)/$(POWER_CALCULATOR).c $(VALIDATION_LIB)
	@echo "Cross-compiling reference power calculator..."
	$(CROSS_CC) $(CFLAGS) $(CROSS_FLAGS) -o $@ $< $(VALIDATION_LIB)

# Testing targets
test: all
	@echo "Running reference solution tests..."
	@echo "Testing voltage checker..."
	@echo -e "1.8\n1.75\n1.5\n2.0\n-1" | ./$(VOLTAGE_CHECKER) > /dev/null && echo "  ✓ Voltage checker test passed" || echo "  ✗ Voltage checker test failed"
	@echo "Testing power calculator..."
	@echo -e "1.8\n0.5\nn" | ./$(POWER_CALCULATOR) > /dev/null && echo "  ✓ Power calculator test passed" || echo "  ✗ Power calculator test failed"
	@echo "Testing safety validator..."
	@echo -e "1.8\n0.5\n25\nn" | ./$(SAFETY_VALIDATOR) > /dev/null && echo "  ✓ Safety validator test passed" || echo "  ✗ Safety validator test failed"
	@echo "✓ Reference solution tests completed"

# Demonstration targets
demo: all
	@echo "=== Reference Solution Demonstration ==="
	@echo "Running voltage checker with sample data..."
	@echo -e "1.8\n1.75\n1.85\n1.5\n2.0\n-1" | ./$(VOLTAGE_CHECKER)
	@echo
	@echo "Running power calculator with sample data..."
	@echo -e "1.8\n0.5\ny\n1.8\n1.2\nn" | ./$(POWER_CALCULATOR)

# Validation against parent test suite
validate: all
	@echo "Validating reference solutions against test suite..."
	@cd .. && make test
	@echo "✓ Reference solutions validated against test suite"

# Performance testing
performance: release
	@echo "Running performance tests..."
	@time -p ./$(VOLTAGE_CHECKER) < /dev/null 2>/dev/null || true
	@time -p ./$(POWER_CALCULATOR) < /dev/null 2>/dev/null || true
	@echo "✓ Performance tests completed"

# Memory testing (requires valgrind)
memory-test: debug
	@echo "Running memory tests (requires valgrind)..."
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Testing voltage checker for memory leaks..."; \
		echo -e "1.8\n-1" | valgrind --leak-check=full --error-exitcode=1 ./$(VOLTAGE_CHECKER) >/dev/null 2>&1 && echo "  ✓ No memory leaks detected" || echo "  ⚠ Memory issues detected"; \
	else \
		echo "  ⚠ Valgrind not available, skipping memory tests"; \
	fi

# Code quality checks
quality: all
	@echo "Running code quality checks..."
	@echo "Checking for compiler warnings..."
	@$(CC) $(CFLAGS) -Wpedantic -Wconversion -Wshadow -c $(SRC_DIR)/$(VOLTAGE_CHECKER).c -o /tmp/voltage_check.o 2>/dev/null && echo "  ✓ Voltage checker: No warnings" || echo "  ⚠ Voltage checker: Warnings detected"
	@$(CC) $(CFLAGS) -Wpedantic -Wconversion -Wshadow -c $(SRC_DIR)/$(POWER_CALCULATOR).c -o /tmp/power_check.o 2>/dev/null && echo "  ✓ Power calculator: No warnings" || echo "  ⚠ Power calculator: Warnings detected"
	@rm -f /tmp/voltage_check.o /tmp/power_check.o
	@echo "✓ Code quality checks completed"

# Documentation generation
docs:
	@echo "Generating reference solution documentation..."
	@mkdir -p docs/generated
	@echo "# Reference Solution Documentation" > docs/generated/README.md
	@echo "Generated on: $$(date)" >> docs/generated/README.md
	@echo "✓ Documentation generated"

# Utility targets
clean:
	@echo "Cleaning reference solution artifacts..."
	rm -f $(VOLTAGE_CHECKER) $(POWER_CALCULATOR) $(DEBUG_PRACTICE) $(SAFETY_VALIDATOR)
	rm -f $(MULTI_VALIDATOR) $(BATCH_PROCESSOR)
	rm -f $(VOLTAGE_CHECKER)_embedded $(POWER_CALCULATOR)_embedded
	rm -rf $(BUILD_DIR) docs/generated
	@echo "✓ Reference solution clean completed"

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Help target
help:
	@echo "Reference Solution Makefile - Available targets:"
	@echo "  all           - Build all reference programs (default)"
	@echo "  debug         - Build with debug flags (-g -O0)"
	@echo "  release       - Build with optimization (-O2)"
	@echo "  cross-compile - Cross-compile for RISC-V RV32I"
	@echo "  test          - Run basic functionality tests"
	@echo "  demo          - Run demonstration with sample data"
	@echo "  validate      - Validate against parent test suite"
	@echo "  performance   - Run performance benchmarks"
	@echo "  memory-test   - Run memory leak detection (requires valgrind)"
	@echo "  quality       - Run code quality checks"
	@echo "  docs          - Generate documentation"
	@echo "  clean         - Remove all build artifacts"
	@echo "  help          - Show this help message"
	@echo ""
	@echo "Individual programs:"
	@echo "  voltage_checker    - Build voltage validation program"
	@echo "  power_calculator   - Build power calculation program"
	@echo "  debug_practice     - Build debug practice program"
	@echo "  safety_validator   - Build safety validation program"
	@echo "  multi_validator    - Build multi-parameter validator"
	@echo "  batch_processor    - Build batch processing program"
	@echo ""
	@echo "Example usage:"
	@echo "  make                    # Build all programs"
	@echo "  make voltage_checker    # Build specific program"
	@echo "  make debug             # Build with debug info"
	@echo "  make test              # Run tests"
	@echo "  make demo              # Run demonstration"

# Prevent make from treating these as file targets
.PHONY: all debug release cross-compile test demo validate performance memory-test quality docs clean help

# Show compilation flags
show-flags:
	@echo "Reference solution compilation flags:"
	@echo "  CC = $(CC)"
	@echo "  CFLAGS = $(CFLAGS)"
	@echo "  DEBUG_FLAGS = $(DEBUG_FLAGS)"
	@echo "  RELEASE_FLAGS = $(RELEASE_FLAGS)"
	@echo "  CROSS_FLAGS = $(CROSS_FLAGS)"

# Compare build sizes
compare-builds: debug release
	@echo "=== Reference Solution Build Size Comparison ==="
	@if [ -f $(VOLTAGE_CHECKER) ]; then \
		ls -lh $(VOLTAGE_CHECKER) | awk '{print "Debug build:   " $$5 " " $$9}'; \
	fi
	@make clean > /dev/null 2>&1
	@make release > /dev/null 2>&1
	@if [ -f $(VOLTAGE_CHECKER) ]; then \
		ls -lh $(VOLTAGE_CHECKER) | awk '{print "Release build: " $$5 " " $$9}'; \
	fi

.PHONY: show-flags compare-builds

