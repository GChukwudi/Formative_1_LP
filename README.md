# Linux Programming Assignment

This repository contains the implementation of four programming tasks on Linux programming, assembly, C/Python integration, and file encryption using shared libraries.

## Overview

This project demonstrates various aspects of low-level programming:
1. Disassembly of executable files using C
2. Assembly language implementation of a calculator
3. System monitoring tool with C extensions for Python
4. File encryption and decryption using shared libraries

## Requirements

- GCC compiler
- Python 3.x with matplotlib
- NASM (Netwide Assembler)
- Linux-based operating system (for /proc filesystem access)

## Task 1: C Program for Disassembly

This component disassembles an executable file and writes the output to a text file.

### Files
- `disassembler.c`: Source code for the disassembler

### Compilation
```
gcc -o disassembler disassembler.c
```

### Usage
```bash
./disassembler <executable_file> disassemble.txt
```

The program uses the `objdump` utility to disassemble the executable and save the output to the specified file.

## Task 2: Assembly Calculator

An assembly program that implements a calculator with five operations: addition, subtraction, multiplication, division, and modulus.

### Files
- `calculator.asm`: Assembly source code for the calculator

### Compilation
```
nasm -f elf64 calculator.asm -o calculator.o
gcc -no-pie calculator.o -o calculator
```

### Usage
Simply run the compiled program:
```
./calculator
```

The program will prompt you to:
1. Select an operation (1-5)
2. Enter the first number
3. Enter the second number

It will then display the result of the calculation.

## Task 3: System Monitoring Tool

A system monitoring tool that uses a C extension with Python to track and visualize CPU usage, memory usage, and network usage.

### Files
- `systemmonitor.c`: C extension source code
- `setup.py`: Python script for building the extension
- `system_monitor.py`: Python script for plotting the data

### Compilation and Installation
```
python3 setup.py build
python3 setup.py install --user
```

### Usage
```
python3 system_monitor.py
```

The program will display a real-time graph showing:
- CPU usage percentage
- Memory usage percentage
- Network usage in bytes/sec

The data is sampled every second, as specified in the requirements.

## Task 4: File Encryption Using Shared Libraries

A file encryption and decryption system using a symmetric key approach with a shared library.

### Files
- `encrypt.c`: Source code for the encryption/decryption library and program to run the encrption and decryption

### Compilation
```
# Compile the shared library
gcc -fPIC -shared -o libencrypt.so encrypt_lib.c

# Compile the executable, linking with the shared library
gcc -o file_encryptor encryptor.c -L. -lencrypt -Wl,-rpath,.
```

### Usage
To encrypt files in the current directory:
```
./file_encryptor encrypt
```

To decrypt encrypted files:
```
./file_encryptor decrypt
```

The program will:
- Find text files in the current directory
- For encryption: Create new files with "enc" appended to the name
- For decryption: Create new files with "dec" appended to the name
- Use a symmetric key of 4 for the encryption/decryption process

## Implementation Details

### Task 1: Disassembler
The disassembler uses the system's `objdump` utility to perform the actual disassembly. The C program handles file management and error checking.

### Task 2: Assembly Calculator
The calculator is implemented in x86-64 assembly language with separate procedures for each operation. It interfaces with C library functions for input/output operations.

### Task 3: System Monitor
The C extension accesses system information from the `/proc` filesystem on Linux:
- CPU usage: Calculated from `/proc/stat`
- Memory usage: Calculated from `/proc/meminfo`
- Network usage: Calculated from `/proc/net/dev`

The Python component uses matplotlib to plot real-time graphs of the collected data.

### Task 4: File Encryption
The encryption uses a simple symmetric shift cipher with a key value of 4:
- Characters are shifted forward by 4 positions for encryption
- Characters are shifted backward by 4 positions for decryption
- The implementation only modifies printable ASCII characters

## License
This project is submitted as part of an academic assignment.