# Day 1: C Fundamentals and Compilation Lab
# Makefile for Chip Parameter Validation System
#
# Learning Objectives:
# - Master GCC compilation with validation-appropriate flags
# - Understand different compilation modes (debug, release, cross-compile)
# - Practice automated build systems for embedded development

# Compiler Configuration
CC = gcc

# Compilation Flags (Following Day 1 Slides)
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
DEBUG_FLAGS = -g -DDEBUG -O0
RELEASE_FLAGS = -O2 -DNDEBUG

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build
DOCS_DIR = docs

# Source Files (TODO: Students will complete these)
SOURCES = $(SRC_DIR)/voltage_checker.c \
          $(SRC_DIR)/power_calculator.c \
          $(SRC_DIR)/debug_practice.c \
          $(SRC_DIR)/safety_validator.c \
          $(SRC_DIR)/multi_validator.c \
          $(SRC_DIR)/batch_processor.c

# Executable Names
VOLTAGE_CHECKER = voltage_checker
POWER_CALCULATOR = power_calculator
DEBUG_PRACTICE = debug_practice
SAFETY_VALIDATOR = safety_validator
MULTI_VALIDATOR = multi_validator
BATCH_PROCESSOR = batch_processor

# Test Executables
TEST_VOLTAGE = $(TEST_DIR)/test_voltage
TEST_POWER = $(TEST_DIR)/test_power

# Validation library
VALIDATION_LIB = $(SRC_DIR)/validation_lib.c

# Validation library
VALIDATION_LIB = $(SRC_DIR)/validation_lib.c

# Default target - builds all main programs and test executables
all: $(VOLTAGE_CHECKER) $(POWER_CALCULATOR) $(SAFETY_VALIDATOR) $(TEST_VOLTAGE) $(TEST_POWER)
	@echo "✓ All Day 1 programs and tests compiled successfully!"
	@echo "Run 'make test' to verify your implementations."

# Individual program targets
$(VOLTAGE_CHECKER): $(SRC_DIR)/voltage_checker.c
	@echo "Compiling voltage checker..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(POWER_CALCULATOR): $(SRC_DIR)/power_calculator.c
	@echo "Compiling power calculator..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(DEBUG_PRACTICE): $(SRC_DIR)/debug_practice.c
	@echo "Compiling debug practice (may have intentional errors)..."
	-$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(SAFETY_VALIDATOR): $(SRC_DIR)/safety_validator.c
	@echo "Compiling safety validator..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $<

# Homework targets
homework: $(MULTI_VALIDATOR) $(BATCH_PROCESSOR)
	@echo "✓ Homework programs compiled successfully!"

$(MULTI_VALIDATOR): $(SRC_DIR)/multi_validator.c
	@echo "Compiling multi-parameter validator..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(BATCH_PROCESSOR): $(SRC_DIR)/batch_processor.c
	@echo "Compiling batch processor..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $<

# Debug builds (Task 3: GCC Compilation Mastery)
debug: CFLAGS += $(DEBUG_FLAGS)
debug: all
	@echo "✓ Debug builds completed with -g -O0 flags"

# Release builds (optimized)
release: CFLAGS += $(RELEASE_FLAGS)
release: all
	@echo "✓ Release builds completed with -O2 optimization"

# Advanced compilation demonstration (Task 4)
advanced: debug release
	@echo "✓ Advanced compilation modes demonstrated"
	@echo "Compare debug vs release builds:"
	@ls -lh $(VOLTAGE_CHECKER) 2>/dev/null || echo "Build programs first with 'make all'"

# Testing targets
test: $(TEST_VOLTAGE) $(TEST_POWER)
	@echo "Running automated tests..."
	./$(TEST_VOLTAGE)
	./$(TEST_POWER)
	@echo "✓ All tests completed"

$(TEST_VOLTAGE): $(TEST_DIR)/test_voltage.c $(VALIDATION_LIB)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

$(TEST_POWER): $(TEST_DIR)/test_power.c $(VALIDATION_LIB)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $< $(VALIDATION_LIB) -lm

# Code quality checks
style-check:
	@echo "Checking code style..."
	@for file in $(SOURCES); do \
		if [ -f $$file ]; then \
			echo "Checking $$file..."; \
			# Basic style checks (can be enhanced with tools like cppcheck)
			grep -n "TODO" $$file || echo "  ✓ No TODO items remaining"; \
		fi; \
	done

# Documentation generation
docs:
	@echo "Generating documentation..."
	@mkdir -p $(DOCS_DIR)/generated
	@echo "# Compilation Log" > $(DOCS_DIR)/COMPILATION_LOG.md
	@echo "Generated on: $$(date)" >> $(DOCS_DIR)/COMPILATION_LOG.md
	@echo "✓ Documentation template created"

# Utility targets
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(VOLTAGE_CHECKER) $(POWER_CALCULATOR) $(DEBUG_PRACTICE) $(SAFETY_VALIDATOR)
	rm -f $(MULTI_VALIDATOR) $(BATCH_PROCESSOR)
	rm -f *.o *.out
	rm -f $(TEST_VOLTAGE) $(TEST_POWER)
	rm -rf $(BUILD_DIR)
	@echo "✓ Clean completed"

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Help target
help:
	@echo "Available targets:"
	@echo "  all           - Build all main programs (default)"
	@echo "  homework      - Build homework programs"
	@echo "  debug         - Build with debug flags (-g -O0)"
	@echo "  release       - Build with optimization (-O2)"
	@echo "  advanced      - Demonstrate advanced compilation modes"
	@echo "  test          - Run automated tests"
	@echo "  style-check   - Check code style and TODO completion"
	@echo "  docs          - Generate documentation templates"
	@echo "  clean         - Remove all build artifacts"
	@echo "  help          - Show this help message"
	@echo ""
	@echo "Example usage:"
	@echo "  make                    # Build all programs"
	@echo "  make voltage_checker    # Build specific program"
	@echo "  make debug             # Build with debug info"
	@echo "  make advanced          # Demonstrate compilation modes"
	@echo "  make test              # Run tests"

# Prevent make from treating these as file targets
.PHONY: all debug release advanced test style-check docs clean help homework

# Advanced features for learning
show-flags:
	@echo "Current compilation flags:"
	@echo "  CC = $(CC)"
	@echo "  CFLAGS = $(CFLAGS)"
	@echo "  DEBUG_FLAGS = $(DEBUG_FLAGS)"
	@echo "  RELEASE_FLAGS = $(RELEASE_FLAGS)"
	@echo "  CROSS_FLAGS = $(CROSS_FLAGS)"

# Demonstrate different compilation modes
demo-compilation:
	@echo "=== Compilation Demonstration ==="
	@echo "1. Debug compilation:"
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -v -c $(SRC_DIR)/voltage_checker.c -o /tmp/debug.o 2>&1 | head -5
	@echo ""
	@echo "2. Release compilation:"
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -v -c $(SRC_DIR)/voltage_checker.c -o /tmp/release.o 2>&1 | head -5
	@echo ""
	@echo "3. Cross-compilation (if toolchain available):"
	-$(CROSS_CC) $(CFLAGS) $(CROSS_FLAGS) -v -c $(SRC_DIR)/voltage_checker.c -o /tmp/cross.o 2>&1 | head -5
	@rm -f /tmp/debug.o /tmp/release.o /tmp/cross.o

# File size comparison
compare-builds: debug release
	@echo "=== Build Size Comparison ==="
	@ls -lh $(VOLTAGE_CHECKER) 2>/dev/null | awk '{print "Debug build:   " $$5 " " $$9}' || echo "Debug build not found"
	@make clean > /dev/null 2>&1
	@make release > /dev/null 2>&1
	@ls -lh $(VOLTAGE_CHECKER) 2>/dev/null | awk '{print "Release build: " $$5 " " $$9}' || echo "Release build not found"

.PHONY: show-flags demo-compilation compare-builds

