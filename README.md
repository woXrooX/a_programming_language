# A Programming Language (APL, a_programming_language)

**Extension:** `.a`

## Overview

APL is a systems-level programming language designed primarily for operating system and systems development. Its syntax is heavily inspired by C, extended with object-oriented programming (OOP) features.

## Ultimate Goal

Build a fully self-bootstrapped stack from the ground up:

1. Write a compiler in raw binary (machine code)
2. Use that compiler to compile APL
3. Use APL to build an operating system from scratch

No external toolchains — the entire chain (compiler → language → OS) is self-made.

## Core Design Decisions

- **Syntax:** C-inspired — nearly identical to C in structure and conventions
- **Target domain:** OS / systems development
- **OOP:** Introduces object-oriented design on top of C fundamentals
- **File extension:** `.a`

## Project History

- Originally named "X Programming Language"
- Renamed to "A Programming Language" (APL)

## Current State

- Core parameters established (extension, syntax model, target domain, OOP)
- Early / definitional stage
- Language design and development ongoing

## Design Notes

Guiding principle: one way to do each thing. See `Docs/main.a` for the target syntax.

- **Statements:** a newline ends a statement. No `;` anywhere. One statement per line.
- **Braces:** optional when an `if`, `else` or `loop` body is a single statement, required when it has several.
- **Loops:** `loop (condition)` is the only loop. No `for`, no `while`. `break` and `continue` are supported.
- **Strings:** two forms, plain `"..."` and formatted `f"..."`.
- **Classes:** the constructor is the reserved word `constructor`, with no return type and one per class. Fields are always accessed through `this.`.
- **Objects:** created with `new`, e.g. `new Point(3, 4)`.
- **Default arguments:** `constructor(int x = 0, int y = 0)`. Parameters with defaults must come last.
- **Named arguments:** `new Point(y = 5)`. Positional arguments first, named after.
- **No overloading:** each name maps to exactly one function. No name mangling; symbols use a plain prefix such as `Point_sum`. (May be revisited.)

*(Add decisions, syntax examples, and design rationale here as the project evolves.)*
