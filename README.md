# simple_atm
A take-home assignment, a simple ATM controller implemented in C++.

- The controller depends on abstract `Bank` and `CashBin` interfaces.
- So real bank system and cash-bin hardware can be integrated later.

---

## Test Environment

This project has been tested on:

| Component | Version |
| --- | --- |
| OS | Ubuntu 22.04.5 LTS (Jammy Jellyfish) |
| Kernel | Linux 6.8.0 (x86_64) |
| Compiler | g++ 11.4.0 |
| CMake | 3.22.1 |

---

## Prerequisites

| Tool | Minimum Version | Notes |
| --- | --- | --- |
| CMake | **3.14+** | — |
| C++ compiler | **C++17 capable** | — |
| Internet access | — | Needed at configure time to download GoogleTest |

On Ubuntu, the toolchain can be installed with:

```bash
sudo apt update
sudo apt install build-essential cmake
```

---

## File Structure

```
simple_atm/
├── CMakeLists.txt                # Build configuration
├── example.cpp                   # Example program
├── include/
│   ├── atm_controller.hpp        # ATM controller declarations
│   ├── bank.hpp                  # Bank interface + Account type
│   └── cash_bin.hpp              # CashBin interface
├── src/
│   └── atm_controller.cpp        # ATM controller implementations
├── test/
│   └── atm_controller_test.cpp   # GoogleTest unit tests
├── LICENSE
└── README.md
```

---

## Build

From the `simple_atm/` directory:

```bash
mkdir build
cd build && cmake ..
make
```

Built executables are as follows.

| Executable | Purpose |
| --- | --- |
| `build/simple_atm` | A short example program which shows a quick illustration of the ATM controller (setup → card insert → PIN → account select → withdraw → deposit → final balance). |
| `build/atm_controller_test` | GoogleTest binary with unit tests covering card insertion, PIN verification (valid/invalid), account selection, withdraw, and deposit. |

### Running

```bash
# Run the example:
./build/simple_atm

# Run the tests:
./build/atm_controller_test
```

