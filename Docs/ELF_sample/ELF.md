```
// RAW

00: 7F 45 4C 46 02 01 01 00  00 00 00 00 00 00 00 00
10: 02 00 B7 00 01 00 00 00  78 00 40 00 00 00 00 00
20: 40 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
30: 00 00 00 00 40 00 38 00  01 00 00 00 00 00 00 00
```

# ELF sample: hand-made "hello" executable

Source of truth for the `ELF` binary in this folder. Every byte in `ELF` is listed here, in order, with its file offset and meaning.

- Target: AArch64 Linux, 64-bit, little-endian
- Load address: `0x400000` (file offset `0x00` lands at memory `0x400000`)
- Multi-byte values are little-endian: lowest byte first

## Layout

| File offset | Size | Part | Status |
|---|---|---|---|
| `0x00` | 64 | ELF header | done |
| `0x40` | 56 | Program header | todo |
| `0x78` | — | Code + `"hello\n"` | todo |

## ELF header (`0x00` – `0x3F`)

```
// Offset  Bytes                     Field          Meaning

//// e_ident: identification, read byte by byte
00         7F 45 4C 46               magic          0x7F 'E' 'L' 'F'
04         02                        class          64-bit
05         01                        data           little-endian
06         01                        version        ELF version 1
07         00                        os_abi         System V
08         00                        abi_version    unused
09         00 00 00 00 00 00 00      padding        reserved, always zero

//// Rest of the header
10         02 00                     e_type         2 = executable
12         B7 00                     e_machine      183 = AArch64
14         01 00 00 00               e_version      1
18         78 00 40 00 00 00 00 00   e_entry        0x400078 = load address + 0x78, first instruction
20         40 00 00 00 00 00 00 00   e_phoff        0x40 = program header right after this header
28         00 00 00 00 00 00 00 00   e_shoff        0 = no section headers
30         00 00 00 00               e_flags        none defined for AArch64
34         40 00                     e_ehsize       64 = size of this header
36         38 00                     e_phentsize    56 = size of one program header
38         01 00                     e_phnum        1 program header
3A         00 00                     e_shentsize    0, no section headers
3C         00 00                     e_shnum        0, no section headers
3E         00 00                     e_shstrndx     0, no section name table
```

## Program header (`0x40` – `0x77`)

Todo.

## Code and data (`0x78` – )

Todo.
