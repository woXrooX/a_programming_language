Mnemonic - Description - Binary Pattern

Legend: d = destination register, t = source register, n = base/target register, i = immediate, h = shift (hw), l = immlo, H = immhi

MOVZ - Move 16-bit immediate into a 64-bit register, zeroing the rest - 1101 0010 1hhi iiii iiii iiii iiid dddd
	hw = 00 for no shift. Example: movz x0, #1 = 0xD2800020

STR - Store 64-bit register to memory (unsigned offset) - 1111 1001 00ii iiii iiii iinn nnnt tttt
	imm12 is the byte offset divided by 8

SVC - Supervisor call (system call) - 1101 0100 000i iiii iiii iiii iii0 0001
	Linux uses imm16 = 0. Example: svc #0 = 0xD4000001

RET - Return from subroutine - 1101 0110 0101 1111 0000 00nn nnn0 0000
	Default return register is x30. Example: ret = 0xD65F03C0

ADR - Load PC-relative address into a register - 0ll1 0000 HHHH HHHH HHHH HHHH HHHd dddd
	Signed 21-bit byte offset from this instruction, split as immhi (high 19 bits) and immlo (low 2 bits)
