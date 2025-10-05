# Day 1: C Fundamentals and Compilation Lab

## Overview

Welcome to the Day 1 lab for C Fundamentals! This assignment introduces core C programming concepts through a practical chip validation system. You'll implement voltage and power validation functions, learn compilation with GCC, and work with a test suite to ensure correctness.

**Learning Objectives:**
- Understand C compilation process and Makefile usage
- Implement basic input validation and error handling
- Work with floating-point arithmetic and precision
- Use header files, structs, and macros effectively
- Write and run unit tests for C programs
- Debug compilation errors and warnings

**Total Points:** 100 (Autograded via GitHub Actions)
- Compilation: 20 pts (All programs build cleanly)
- Voltage Tests: 40 pts (10 tests, 4 pts each)
- Power Tests: 40 pts (10 tests, 4 pts each)

## Repository Structure

```
day1-c-fundamentals/
├── include/
│   └── validation.h      # Shared headers, constants, and prototypes
├── src/
│   ├── validation_lib.c  # Shared validation functions (implement these!)
│   ├── voltage_checker.c # Task 1: Basic voltage validation
│   ├── power_calculator.c # Task 2: Power calculation and efficiency
│   ├── safety_validator.c # Task 3: Combined safety checks
│   ├── multi_validator.c # Extension: Multi-parameter validation
│   └── batch_processor.c # Extension: Batch processing
├── tests/
│   ├── test_voltage.c    # Unit tests for voltage functions
│   └── test_power.c      # Unit tests for power functions
├── config/
│   └── chip_specs.txt    # Configuration file for multi-validator
├── Makefile              # Build system (do not modify unless instructed)
└── README.md             # This file
```

## Setup Instructions

### Linux/macOS (Recommended)
1. **Clone the Repository:**
   ```
   git clone <your-github-classroom-repo-url>
   cd day1-c-fundamentals
   ```

2. **Install Dependencies:**
   - Ensure GCC and Make are installed (usually pre-installed on Linux/macOS).
   - On Ubuntu/Debian: `sudo apt update && sudo apt install build-essential`
   - On macOS: Install Xcode Command Line Tools via `xcode-select --install`

3. **Build and Test:**
   ```
   make clean
   make all    # Compiles all programs
   make test   # Runs unit tests (should pass 10/10 for voltage + power)
   ```

### Windows Setup
Windows requires additional setup since the project uses Unix-style tools (GCC, Make). We recommend **Windows Subsystem for Linux (WSL)** for the best experience, as it matches the GitHub Actions CI environment (Ubuntu 24.04).

#### Option 1: Windows Subsystem for Linux (WSL) – Easiest and Recommended
WSL provides a full Linux environment inside Windows.

1. **Install WSL:**
   - Open PowerShell as Administrator and run: `wsl --install`
   - This installs WSL 2 with Ubuntu (reboot if prompted).
   - Launch Ubuntu from the Start menu and set up a username/password.

2. **Install Dependencies in WSL:**
   - Open the Ubuntu terminal.
   - Update packages: `sudo apt update`
   - Install build tools: `sudo apt install build-essential git`

3. **Clone and Work in WSL:**
   - In Ubuntu terminal: `git clone <your-repo-url>`
   - `cd day1-c-fundamentals`
   - Follow Linux instructions above: `make clean && make all && make test`

4. **Access Files in Windows:**
   - Your project files are in `\\wsl$\Ubuntu\home\<username>\day1-c-fundamentals`
   - Edit in VS Code (install "Remote - WSL" extension) or Windows Explorer.

**Pros:** Identical to CI; full Linux tools. **Cons:** Slight learning curve if new to Linux.

#### Option 2: Native Windows with MinGW-w64 (No WSL)
Use MinGW for GCC/Make on Windows.

1. **Install MinGW-w64:**
   - Download from [MSYS2](https://www.msys2.org/) (recommended).
   - Install MSYS2, then open MSYS2 terminal and run:
     ```
     pacman -Syu
     pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-git
     ```
   - Add MinGW bin to PATH: `C:\msys64\mingw64\bin`

2. **Install VS Code (Optional but Recommended):**
   - Download from [code.visualstudio.com](https://code.visualstudio.com/).
   - Install extensions: "C/C++" (Microsoft), "Makefile Tools".

3. **Clone and Build:**
   - Open MSYS2 MinGW terminal (not MSYS2 base).
   - `git clone <your-repo-url>`
   - `cd day1-c-fundamentals`
   - `mingw32-make clean && mingw32-make all && mingw32-make test`
     - Note: Use `mingw32-make` instead of `make`.

**Pros:** Native Windows. **Cons:** Potential path issues; less identical to CI.

#### Option 3: VS Code with Dev Containers (Advanced)
- Install VS Code + "Dev Containers" extension.
- Use a Dockerfile for Ubuntu + GCC (create `.devcontainer/devcontainer.json` if needed).
- Reopen in container: Automatically sets up Linux env.

**Troubleshooting Windows:**
- **Path Issues:** Use forward slashes (`/`) in code; avoid spaces in paths.
- **Compilation Errors:** Ensure `-std=c11` and `-lm` (math lib).
- **Git Bash:** If using Git for Windows, it has basic Make but install MinGW for full GCC.
- **Test Failures:** Run tests in the exact env (WSL preferred) to match CI.

## Building and Testing

- **Clean Build:** `make clean` (removes binaries).
- **Compile All:** `make all` (builds executables: voltage_checker, power_calculator, etc.).
- **Run Tests:** `make test` (compiles and runs voltage/power tests; expect 100% pass).
- **Run Programs:**
  ```
  ./voltage_checker     # Interactive voltage input
  ./power_calculator    # Voltage + current to power
  ./multi_validator     # Multi-param with config file
  ```
- **Debug:** Use `gdb ./voltage_checker` or VS Code debugger. Enable `DEBUG_PRINT` macros.

**Expected Test Output:**
```
Voltage tests: 10/10 passed
Power tests: 10/10 passed
✓ All tests completed
```

## Tasks to Complete

### In-Class (Basics – 60 pts)
1. **voltage_checker.c:** Read voltage, validate against 1.8V ±5%, print PASS/FAIL with colors.
2. **power_calculator.c:** Read V/I, compute power, check vs. 2W limit, categorize efficiency.
3. **validation_lib.c:** Implement `validate_voltage`, `calculate_power`, `is_power_acceptable`, `format_validation_result`, and stats functions.

### Homework (Extensions – 40 pts)
4. **safety_validator.c:** Combined checks for voltage, current, power, temperature.
5. **multi_validator.c:** Parse `config/chip_specs.txt`, support 1.8V/3.3V variants, multi-param validation with reports.
6. **batch_processor.c:** Batch mode with file input and stats summary.

**Do Not:**
- Modify `Makefile` or test files (they're autograder-provided).
- Change basic `ValidationResult` struct in `validation.h` (breaks tests).
- Forget to handle input errors (e.g., non-numeric input).

## Assessment and Submission

- **Autograding:** Every push to `main` triggers GitHub Actions (Actions tab). Score based on compilation + tests.
- **Full Score (100/100):** All programs compile; tests pass 100%.
- **Submission:** Commit changes (`git add . && git commit -m "Implemented voltage validation"`) and push (`git push origin main`). No separate submission—CI handles grading.
- **Partial Credit:** Tests give points per passing case; fix incrementally.

**Timeline:** Complete in-class by end of lab; homework by [deadline]. Ask questions on [course forum]!

## Troubleshooting

- **Compilation Errors:** Check includes (`#include "../include/validation.h"`), fix warnings (`-Wall`).
- **Test Failures:** Read FAIL messages (e.g., "Nominal voltage should be valid"). Verify `is_valid` logic.
- **Config Parsing:** In multi_validator, handle missing file with defaults; trim whitespace.
- **Windows-Specific:** If issues, switch to WSL—it's the most reliable.
- **CI vs. Local:** If local passes but CI fails, check env (use WSL) or uncommitted changes (`git status`).

Happy coding! 🚀

