# Representing Instructions in the Computer

Instructions are kept in the computer as a series of high and low electronic signals and may be represented as numbers.
In fact, each piece of an instruction can be considered as an individual number, and placing these numbers side by side forms the instruction.

### Example:(Translating a RISC-V Assembly Instruction into a Machine Instruction)
```assembly
    add x9, x20, x21
```

The decimal representation is

|     |     |     |     |     |     |
|:---:|:---:|:---:|:---:|:---:|:---:|
|  0  | 21  | 20  |  0  |  9  | 51  |

Each of these segments of an instruction is called a **field**.

The first, fourth, and sixth fields (0, 0, 51) collectively tell the RISC-V computer that this performs addition.

This instruction can also be represented as fields of binary:

|     |     |     |     |     |     |
|:---:|:---:|:---:|:---:|:---:|:---:|
0000000 | 10101 | 10100 | 000 | 01001 | 0110011

This layout of the instruction is called the **instruction format*.
This instruction takes exactly 32 bits, a word.
All RISC-V instructions are all 32 bits long.

**instruction format**:

A form of representation of an instruction composed of fields of binary numbers.

**machine language**:

Binary representation used for communication within a computer system.

**Hexadecimal**:

Numbers in base 16.

## RISC-V Fields
RISC-V fields are given names to make them easier to discuss:

|funct7|rs2|rs1|funct3|rd|opcode|
|:---:|:---:|:---:|:---:|:---:|:---:|
7 bits|5 bits|5 bits|3 bits|5 bits|7 bits  

- **opcode**: Basic operation of the instruction, and this abbreviation is its traditional name.
- **rd**: The register destination operand. It gets the result of the operation.
- **funct3**: An additional opcode field.
- **rs1**: The first register source operand.
- **rs2**: The second register source operand.
- **funct7**: An additional opcode field.

**opcode**: The field that denotes the operation and format of an instruction.

A problem occurs when an instruction needs longer fields than shown above. For example, the *load register instruction* must specify two registers and a constant.

*Hardware Design Principle 3: Good design demands good compromises.*

The compromise chosen by the RISC-V designers is to keep all instructions the same length, thereby requiring distinct instruction formats for different kinds of instructions.

**R-type**

|funct7|rs2|rs1|funct3|rd|opcode|
|:---:|:---:|:---:|:---:|:---:|:---:|
7 bits|5 bits|5 bits|3 bits|5 bits|7 bits  

**I-type** 

used by arithmetic operands with one constant operand, addi, and by load instructions.

|immediate|rs1|funct3|rd|opcode|
|:---:|:---:|:---:|:---:|:---:|
12 bits|5 bits|3 bits|5 bits|7 bits

The 12-bit immediate is interpreted as a two's complement value. For load instructions, the immediate represents a *byte offset*.

We can see that more than 32 registers would be difficult, as the rd and rs1 fields would each need another bit, making it harder to fit everything in one word.

We also need a format for the store double word instruction, sd, which needs two source registers and an immediate for the address offset.

**S-type**

|immediate[11:5]|rs2|rs1|funct3|immediate[4:0]|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
7 bits|5 bits|5 bits|3 bits|5 bits|7 bits  

To keep the same structure, RISC-V architects divided immediate into two parts.

The formats are distinguished by the values in the first field (opcode).

## Example:(Translating RISC-V Assembly Language into Machine Language)
x10 has the base of the array A and x21 corresponds to h.

```c
    A[30] = h + A[30] + 1;
```
```assembly
    ld x9, 240(x10) // Temp reg x9 gets A[30]
    add x9, x21, x9 // Temp reg x9 gets h + A[30]
    addi x9, x9, 1 // Temp reg x9 gets h + A[30] + 1
    sd x9, 240(x10) // Stores h+A[30]+1 back into A[30]
```
What is the RISC-V machine language code for these three instructions?

Let's represent the machine language instructions using decimal numbers.

**ld**

|immediate|rs1|funct3|rd|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|
240|10|3|9|3

**add**

|funct7|rs2|rs1|funct3|rd|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
0|9|21|0|9|51

**addi**

|immediate|rs1|funct3|rd|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|
1|9|0|9|19

**sd**

|immediate[11:5]|rs2|rs1|funct3|immediate[4:0]|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
7|9|10|3|16|35

Here, 240 in binary is 11111000. So, 0000111 and 10000 => 7 and 16

Finally, binary representations will be:

**ld**

|immediate|rs1|funct3|rd|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|
000011110000|01010|011|01001|0000011

**add**

|funct7|rs2|rs1|funct3|rd|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
0000000|01001|10101|000|01001|0110011

**addi**

|immediate|rs1|funct3|rd|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|
000000000001|01001|000|01001|0010011

**sd**

|immediate[11:5]|rs2|rs1|funct3|immediate[4:0]|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
0000111|01001|01010|011|10000|0100011

### NOTE:
RISC-V assembly language programmers aren't forced to use *addi* when working with constants.
The assembler generates the proper opcode and the proper instruction format.

### NOTE:
Although RISC-V has *add* and *sub* instructions, it does not have a *subi*.
This is because the immediate field of *addi* represents a two's complement integer.

## The BIG Picture
1. Instructions are represented as numbers.
2. Programs are stored in memory to be read or written, just like data.

These principles lead to the **stored-program** concept.
Memory can contain the source code for an editor program, the corresponding compiled machine code, the text that the compiled program is using, and even the compiler that generated the machine code.

One consequence of instructions as numbers is that programs are often shipped as files of binary numbers. 
The commercial implication is that computers can inherit ready-made software provided they are compatible with an existing instruction set.
Such "binary compatibility" often leads industry to align around a small number of instruction set architectures.

