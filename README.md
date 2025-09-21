# Day 1: C Fundamentals and Compilation Lab
## Chip Parameter Validation System

###  Learning Objectives
By the end of this assignment, you will be able to:
1. **Understand C syntax and basic data types** for validation contexts (int, float, char, double)
2. **Write programs with variables and operators** for chip parameter testing
3. **Use printf/scanf** for validation input/output operations
4. **Compile programs with GCC** using validation-appropriate flags (-Wall, -g, -O2, -std=c11)
5. **Create validation calculations** for chip parameters (voltage, current, power)
6. **Handle basic compilation errors** and debugging techniques

### ⏰ Time Allocation
- **In-Class Lab:** 3.5 hours (210 minutes)
- **Homework Extension:** 2 hours (120 minutes)
- **Total:** 5.5 hours

---

##  Assignment Overview

You will build a **Chip Parameter Validation System** that demonstrates fundamental C programming concepts in the context of post-silicon validation engineering. This assignment follows directly from Day 1 slides covering C syntax, data types, compilation, and basic validation scenarios.

### Real-World Context
Post-silicon validation engineers need to verify that manufactured chips operate within specified parameters. Your validation system will check voltage levels, calculate power consumption, and ensure chips meet operational requirements - exactly the kind of work you'll do in industry.

---

##  In-Class Tasks (3.5 hours)

### Task 1: Data Types for Validation (45 minutes)
**Objective:** Implement a voltage checker using appropriate C data types

**What you'll learn:**
- Choosing correct data types for different validation scenarios
- Variable declarations and basic arithmetic operators
- Input validation and range checking

**Implementation:**
- Complete `src/voltage_checker.c`
- Use `float` for voltage values (precision needed)
- Use `int` for pass/fail counts
- Use `char` for status flags
- Implement voltage range checking (1.8V ± 5%)

**Expected Output:**
```
Enter voltage reading: 1.85
✓ PASS: Voltage 1.85V is within acceptable range (1.71V - 1.89V)
```

### Task 2: Input/Output for Chip Testing (45 minutes)
**Objective:** Create a power consumption calculator with user interaction

**What you'll learn:**
- Using printf/scanf for user input and formatted output
- Mathematical operations for engineering calculations
- Error handling for invalid inputs

**Implementation:**
- Complete `src/power_calculator.c`
- Calculate power = voltage × current
- Handle multiple chip configurations
- Implement input validation and error messages

**Expected Output:**
```
=== Power Consumption Calculator ===
Enter voltage (V): 1.8
Enter current (A): 0.5
Power consumption: 0.90W
Status: Within normal operating range
```

### Task 3: GCC Compilation Mastery (60 minutes)
**Objective:** Master GCC compilation with validation-appropriate flags

**What you'll learn:**
- Using GCC flags: -Wall, -g, -O2, -std=c11
- Understanding compilation errors and warnings
- Creating and using Makefiles for automated builds

**Implementation:**
- Complete the provided Makefile
- Fix intentional compilation errors in `src/debug_practice.c`
- Practice compiling with different optimization levels
- Document compilation process in `docs/COMPILATION_LOG.md`

**Commands to master:**
```bash
gcc -Wall -g -std=c11 -o voltage_checker src/voltage_checker.c
make all
make clean
make debug
```

### Task 4: Cross-Compilation Introduction (45 minutes)
**Objective:** Introduction to cross-compilation for embedded targets

**What you'll learn:**
- Difference between native and cross-compilation
- Introduction to riscv64-unknown-elf-gcc
- Basic embedded development concepts

**Implementation:**
- Use provided cross-compilation script
- Compare desktop vs embedded compilation
- Document differences in `docs/CROSS_COMPILATION_NOTES.md`

**Commands to try:**
```bash
./scripts/cross_compile.sh voltage_checker
file voltage_checker_desktop
file voltage_checker_embedded
```

### Task 5: Memory Safety Basics (35 minutes)
**Objective:** Implement basic memory safety and error handling

**What you'll learn:**
- Variable initialization best practices
- Input validation techniques
- Basic error handling patterns

**Implementation:**
- Complete `src/safety_validator.c`
- Add comprehensive input validation
- Implement graceful error recovery
- Test with invalid inputs

---

##  Homework Extensions (2 hours)

### Task 6: Enhanced Validation Suite (60 minutes)
**Objective:** Create a comprehensive multi-parameter validation system

**Requirements:**
- Read chip specifications from `config/chip_specs.txt`
- Validate voltage, current, temperature, and frequency
- Generate detailed validation reports
- Support multiple chip configurations

**Deliverables:**
- Enhanced `src/multi_validator.c`
- Updated configuration file format
- Validation report generation

### Task 7: Batch Processing Mode (60 minutes)
**Objective:** Add batch processing capabilities for automated testing

**Requirements:**
- Process multiple test cases from file
- Generate summary statistics
- Export results in CSV format
- Add command-line argument processing

**Deliverables:**
- Batch processing functionality
- Test case file format documentation
- Results export system

---

##  Repository Structure

```
day1-c-fundamentals-[username]/
├── README.md                    # This file - assignment instructions
├── Makefile                     # Build configuration with proper flags
├── .gitignore                   # C development gitignore
├── src/
│   ├── voltage_checker.c        # Task 1: Voltage validation (TEMPLATE)
│   ├── power_calculator.c       # Task 2: Power calculations (TEMPLATE)
│   ├── debug_practice.c         # Task 3: Compilation practice (BUGGY)
│   ├── safety_validator.c       # Task 5: Memory safety (TEMPLATE)
│   ├── multi_validator.c        # Task 6: Multi-parameter validation (HOMEWORK)
│   └── batch_processor.c        # Task 7: Batch processing (HOMEWORK)
├── include/
│   ├── validation.h             # Common validation functions
│   └── chip_specs.h            # Chip specification structures
├── config/
│   ├── chip_specs.txt          # Sample chip configurations
│   └── test_cases.txt          # Test case definitions
├── tests/
│   ├── test_voltage.c          # Unit tests for voltage validation
│   ├── test_power.c            # Unit tests for power calculations
│   └── expected_outputs/       # Expected output files for testing
├── docs/
│   ├── COMPILATION_LOG.md      # Task 3: Compilation documentation
│   ├── CROSS_COMPILATION_NOTES.md # Task 4: Cross-compilation notes
│   └── VALIDATION_SPECS.md     # Chip validation requirements
├── scripts/
│   ├── cross_compile.sh        # Cross-compilation helper script
│   └── run_tests.sh           # Automated testing script
└── .github/
    └── workflows/
        └── ci.yml              # Automated testing workflow
```

---

##  Testing Your Work

### Automated Testing
Your repository includes automated tests that run on every commit:

```bash
# Run all tests locally
make test

# Run specific test suites
./tests/test_voltage
./tests/test_power

# Check code style
make style-check
```

### Manual Testing
Test your programs with various inputs:

```bash
# Test voltage checker with different values
echo "1.85" | ./voltage_checker
echo "2.0" | ./voltage_checker    # Should fail
echo "1.5" | ./voltage_checker    # Should fail

# Test power calculator
echo -e "1.8\n0.5" | ./power_calculator
```

---

##  Assessment Criteria (150 points total)

### Code Functionality (60 points)
- **Task 1 - Voltage Checker (15 pts):** Correct data types, range validation
- **Task 2 - Power Calculator (15 pts):** Accurate calculations, input handling
- **Task 3 - Compilation (10 pts):** Successful compilation with all flags
- **Task 4 - Cross-compilation (10 pts):** Understanding of embedded concepts
- **Task 5 - Safety Validator (10 pts):** Proper error handling and validation

### Code Quality (30 points)
- **Style and Formatting (10 pts):** Consistent indentation, naming conventions
- **Comments and Documentation (10 pts):** Clear, helpful comments
- **Code Organization (10 pts):** Logical structure, proper use of functions

### Compilation and Testing (25 points)
- **Makefile Usage (10 pts):** Proper build configuration
- **Error Handling (10 pts):** Graceful handling of invalid inputs
- **Test Passage (5 pts):** All automated tests pass

### Documentation (20 points)
- **README Updates (5 pts):** Document your implementation approach
- **Compilation Log (10 pts):** Detailed compilation documentation
- **Code Comments (5 pts):** Inline documentation of complex logic

### GitHub Workflow (15 points)
- **Commit Quality (10 pts):** Descriptive commit messages, logical commits
- **Pull Request (5 pts):** Proper PR creation and description

### Extra Credit Opportunities (up to 25 points)
- **Advanced Features:** Additional validation parameters, GUI interface
- **Performance Optimization:** Efficient algorithms, memory usage optimization
- **Creative Extensions:** Novel validation approaches, industry-relevant features

---

##  Getting Started

### 1. Accept the Assignment
Click the GitHub Classroom invitation link to create your personal repository.

### 2. Clone Your Repository
```bash
git clone https://github.com/[course-org]/day1-c-fundamentals-[username].git
cd day1-c-fundamentals-[username]
```

### 3. Set Up Development Environment
```bash
# Install required tools (if not already installed)
sudo apt update
sudo apt install gcc make git

# Test your setup
make --version
gcc --version
```

### 4. Start with Task 1
```bash
# Open the first template file
code src/voltage_checker.c  # or use your preferred editor

# Read the TODO comments and implement the required functionality
# Test your implementation
make voltage_checker
./voltage_checker
```

### 5. Commit Your Progress
```bash
git add src/voltage_checker.c
git commit -m "Implement Task 1: Voltage checker with range validation"
git push origin main
```

---

##  Tips for Success

### Programming Best Practices
1. **Read TODO comments carefully** - they provide step-by-step guidance
2. **Test frequently** - compile and test after each small change
3. **Use meaningful variable names** - `voltage_reading` not `v`
4. **Add comments** - explain your logic, especially for calculations
5. **Handle edge cases** - what happens with negative inputs?

### Debugging Strategies
1. **Start simple** - get basic functionality working first
2. **Use printf for debugging** - print variable values to understand program flow
3. **Read compiler messages** - they often tell you exactly what's wrong
4. **Test with known values** - use inputs where you know the expected output

### Time Management
- **Task 1-2:** Focus on correctness first, optimization later
- **Task 3:** Don't skip the compilation practice - it's crucial for later days
- **Task 4:** Understand concepts even if cross-compilation doesn't work perfectly
- **Task 5:** Error handling is as important as main functionality

---

##  Getting Help

### Resources Available
- **Office Hours:** [Schedule and location]
- **Discussion Forum:** [Link to course forum]
- **Peer Collaboration:** Encouraged for concepts, not code copying
- **Documentation:** Extensive docs/ folder with guides and references

### Common Issues and Solutions
- **Compilation Errors:** Check syntax, missing semicolons, unmatched braces
- **Linker Errors:** Ensure all functions are defined, check Makefile
- **Runtime Errors:** Use printf debugging, check for uninitialized variables
- **Git Issues:** Ask for help early, don't wait until submission deadline

### Academic Integrity
- **Collaboration:** Discuss concepts and approaches with peers
- **Individual Work:** All code must be your own implementation
- **AI Tools:** Document any AI assistance in comments
- **Citations:** Credit any external resources or references used

---

##  Submission Instructions

### Final Checklist
- [ ] All tasks completed and tested
- [ ] Code compiles without warnings
- [ ] All automated tests pass
- [ ] Documentation updated
- [ ] Commit messages are descriptive
- [ ] Code is properly commented

### Submission Process
1. **Final Commit:** Ensure all changes are committed and pushed
2. **Create Pull Request:** Create PR from your main branch to submission branch
3. **PR Description:** Summarize your implementation and any challenges faced
4. **Submit PR Link:** Submit your PR URL via the course submission form

### Deadline
**Due:** [Insert specific deadline]
**Late Policy:** [Insert late policy details]

---

**Good luck with your first C programming assignment! Remember, this is the foundation for everything we'll build in the remaining days of the course. Take your time to understand the concepts thoroughly.**

