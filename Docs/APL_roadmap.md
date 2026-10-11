# APL Roadmap: Batch 1 (Language & Compiler)

## Context

- **Project:** A Programming Language (APL), a C-inspired systems language with OOP, file extension `.a`
- **Ultimate goal:** my own OS, written in my own language, compiled by my own compiler. No external toolchains.
- **Two batches:**
  1. **Batch 1 (current):** language and compiler
  2. **Batch 2 (future):** OS development
- **Target architecture:** generic ARMv8-A, 64-bit (AArch64). No 32-bit ARM, no Thumb, no Apple-specific features.
- **Development host:** AArch64 Linux running in a VM (UTM or QEMU) on Apple Silicon. Reasons:
  - ELF output, which is simple to write by hand
  - stable syscall interface
  - no code signing
  - native speed
- **Rule for the whole batch:** never rely on libc. Each tool uses raw syscalls only. This keeps the chain self-made and eases the move to bare metal in Batch 2.

---

## Stage 0: Hex loader

- **Written in:** raw machine code (bytes typed in a hex editor)
- **Does:** reads a hex text file and writes out the binary bytes it describes
- **Learn first:**
  - AArch64 instruction encoding
  - the ELF64 header
  - the Linux syscalls for reading, writing, opening files and exiting
- **Warm-up milestone:** a hand-made ELF that prints "hello" and exits

## Stage 1: Minimal assembler

- **Written in:** hex, built by Stage 0
- **Does:** turns mnemonics into instructions and resolves labels, so branch offsets no longer need computing by hand
- **Scope:** only the 20–30 instructions actually used

## Stage 2: Full assembler

- **Written in:** Stage 1 assembly
- **Adds:** macros, constants, a data section, possibly multiple files
- **Output:** ELF executables, plus raw flat binaries for Batch 2

## Stage 3: APL-0 compiler

- **Written in:** Stage 2 assembly
- **Compiles:** a tiny C-like subset of APL: integers, pointers, functions, `if`/`loop`, globals
- **Output:** Stage 2 assembly text
- **Decide on paper first:**
  - the APL-0 grammar
  - the calling convention (adopt AAPCS64, the standard AArch64 one)

## Stage 4: Self-hosting

- **Written in:** APL-0, built by Stage 3
- **Milestone:** the compiler compiles its own source, and that output does the same, producing identical results
- **After this:** stop writing assembly except for tiny runtime pieces

## Stage 5: Grow the language

- **Written in:** APL, compiling itself
- **Order:**
  1. structs
  2. arrays and strings
  3. a module/import system
  4. OOP (classes, methods, vtables)
  5. remaining APL features
- **Alongside:**
  - a small standard library written in APL on raw syscalls
  - a test suite that every compiler change must pass before it is accepted

---

## Batch 1 exit criteria (ready for the OS)

1. The compiler is self-hosting and stable.
2. It can emit a freestanding flat binary with no OS assumptions and a chosen load address.
3. APL can express what a kernel needs:
   - inline or linked assembly for special instructions
   - precise struct layout
   - volatile memory access

**Batch 2 (OS)** starts on the QEMU `virt` machine (AArch64), using the Stage 5 compiler. Real hardware comes later, Raspberry Pi first, then optionally Apple Silicon. The kernel keeps a thin platform layer (memory map, UART, interrupt controller) separate from the core.

---

## Current position

**Before Stage 0.** Current work:

- learning AArch64 encoding, ELF64 and Linux AArch64 syscalls
- the hand-made "hello" ELF warm-up

## Reference material

- *Arm Architecture Reference Manual (A-profile)*: instruction encoding
- ELF-64 specification (System V ABI, AArch64 supplement)
- Linux AArch64 syscall table
- AAPCS64 (Procedure Call Standard for the Arm 64-bit Architecture)
- Bootstrapping examples: stage0 / live-bootstrap, sectorforth
