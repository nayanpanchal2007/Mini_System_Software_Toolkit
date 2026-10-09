# Mini System Software Toolkit

A compact C-based system software toolkit built to demonstrate the core phases of compiler construction and low-level software tools. It provides a simple command-line interface for experimenting with lexical analysis, symbol table management, assembler logic, macro expansion, linking, parsing, intermediate code generation, and basic code optimization.

This project is designed for academic and learning purposes and is intentionally simple, making it easy to understand how system software components work at a foundational level.

## Overview

The toolkit includes the following modules:

- Lexical Analyzer
- Symbol Table Manager
- Two-Pass Assembler
- Macro Processor
- Linker and Loader Simulation
- Recursive Descent Parser
- Quadruple Generator
- Code Optimizer

Together, these modules model the essential stages of a basic compiler and assembler pipeline.

## Features

### 1. Lexical Analyzer
The lexical analyzer reads an input source string, tokenizes it, and identifies:

- keywords
- identifiers
- numbers
- operators
- punctuation

It also inserts non-keyword identifiers into the symbol table automatically.

### 2. Symbol Table
A simple symbol table stores identifiers with their:

- name
- type
- address

This supports quick lookup and display of the symbol inventory used during assembly and parsing.

### 3. Two-Pass Assembler
The assembler performs a simplified two-pass assembly process:

- Pass 1: assigns location counter values and builds the symbol table
- Pass 2: generates object-code-like output for each instruction

It supports a small instruction set such as `START`, `LDA`, `STA`, `ADD`, `SUB`, and `END`.

### 4. Macro Processor
The macro processor accepts macro definitions in a simple format and expands them in the input stream. It demonstrates how code can be reused through macro definitions and expansion.

### 5. Linker / Loader Simulation
This module simulates linking multiple object modules by accepting module names and sizes, calculating their load addresses, and displaying the total linked program size and entry point.

### 6. Recursive Descent Parser
The parser checks whether an arithmetic expression is syntactically valid according to a simple grammar:

- `E -> T {(+|-) T}`
- `T -> F {(*|/) F}`
- `F -> id | num | (E)`

It accepts valid arithmetic expressions and rejects invalid ones.

### 7. Quadruple Generator
The quadruple generator converts a simple assignment expression into intermediate code in quadruple form:

- operation
- first operand
- second operand
- result

This demonstrates a low-level representation commonly used in compiler backends.

### 8. Code Optimizer
The optimizer works on the last generated quadruple list and applies basic optimization techniques:

- constant folding
- copy propagation

This provides a simple demonstration of optimization strategies used in compiler design.

## Project Structure

```text
Mini_System_Software_Toolkit/
├── assembler.c          # Two-pass assembler implementation
├── lexical.c            # Lexical analyzer implementation
├── linker_loader.c      # Linker/loader simulation
├── macro.c              # Macro processor implementation
├── main.c               # Menu-driven program entry point
├── optimizer.c          # Code optimization logic
├── parser.c             # Recursive descent parser
├── quadruple.c          # Intermediate code generation
├── symbol_table.c       # Symbol table logic
├── toolkit.h            # Shared declarations and structures
├── toolkit.exe          # Compiled Windows executable
├── .gitignore           # Git ignore rules
└── README.md            # Project documentation
```

## Requirements

- A C compiler such as GCC or MinGW
- Command Prompt, PowerShell, or a Unix-like terminal
- No external libraries are required

## Build Instructions

### Windows (MinGW/GCC)

```bash
gcc -std=c11 -Wall -Wextra -o toolkit.exe main.c assembler.c lexical.c symbol_table.c macro.c linker_loader.c parser.c quadruple.c optimizer.c
```

### Linux/macOS

```bash
gcc -std=c11 -Wall -Wextra -o toolkit main.c assembler.c lexical.c symbol_table.c macro.c linker_loader.c parser.c quadruple.c optimizer.c
```

## Run the Program

### Windows

```bash
toolkit.exe
```

### Linux/macOS

```bash
./toolkit
```

## Menu Options

When the program starts, it displays a menu:

1. Lexical Analyzer
2. Symbol Table
3. Two Pass Assembler
4. Macro Processor
5. Linker / Loader
6. Recursive Descent Parser
7. Quadruple Generator
8. Code Optimizer
9. Display Symbol Table
0. Exit

## Example Usage

### Lexical Analysis Input

```text
int a = 10 + 20;
```

This identifies tokens such as `int`, `a`, `=`, `10`, `+`, `20`, `;`.

### Parser Input

```text
a + b * c
```

This is a valid arithmetic expression under the parser grammar.

### Assembler Example

```text
START 1000
LDA A
ADD B
STA C
END
```

This demonstrates location-counter tracking and symbol assignment.

### Macro Example

```text
MACRO ADDM
LDA A
ADD B
MEND
ADDM
END
```

This shows a macro definition followed by expansion.

## Notes

This is an educational mini toolkit rather than a full production compiler or operating system utility. The implementation prioritizes clarity and understanding over production-level robustness. It is best suited for learning system software concepts, compiler phases, and assembly-related operations.

## License

This project is provided for academic and educational use.
