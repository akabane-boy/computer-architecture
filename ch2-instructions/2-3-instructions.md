# Instruction

## Operands of the Computer Hardware

RISC-V is 64-bit architecture.
That means 1 register have 64-bits size.
**Registers** are the primitives used in hardware design and used as operands of arithmetic instructions.

**doubleword** - 64 bits
**word** - 32 bits

RISC-V has **32** of registers.

Reason:
1. Not to increase the clock cycle time.
2. Number of bits it would take in the instruction format.

x0 ~ x31

## Memory Operands

Registers handles small amount of data but computer memory has billions of data elements. Hence, data structures(arrays and structures) are kept in memory.

RISC-V must include instruction that transfer data between registers and memory.
Such are called **data transfer instructions**.

**Memory** is a large, single-dimensionla array with the address.

([adress] value,)
[0] 1, [1] 101, [2] 10, [3] 100, ...

The data transfer instructions is called *load*.

The format of the load instruction:
name of the operation, register to be loaded, register, constant

### Example:(Compiling an Assignment When an Operand Is in Memory

A is and array of 100 doublewords, g -> x20, h -> x21, and base address(starting address) of the array A is in x22.
Compile below:
```c
    g = h + A[8];
```
1. Transfer A[8] to a register.

```assembly
ld x9, 8(x22) // Temoporary reg x9 gets A[8]

add x20, x21, x9 // g = h + A[8]
```

The register added to form the address (x22) is called the **base register**.
The constant in a data tranfer instruction (8) is called the **offset**.

### Byte Addressing

8-bit *bytes*. So 64-bits are 8 bytes.
Virtually all architectures today address individual *bytes*. So address of one of the bytes in doubleword matches with another in same doubleword. And sequential doublewords differ by 8 bytes.

([byte adress] value,)
[0] 1, [8] 101, [16] 10, [24] 100, ...

**Big endian**: Those that use the address of the leftmost or "big end" byte as the doubleword adress
**Little endian**(RISC-V): Those that use the address of the rightmost or "little end" byte as the doubleword adress

Instruction complementary to load is called *store*; it copies data from a register to memory.
```assembly
sd
```
*store doubleword*

**Alignment restriction**: words must start at addresses that are multiples of 4 and doublewords must start at addresses that are multiples of 8.

### Example:(Compiling Using Load and Store)
Assume variable h -> x21 and the base address of the array A is in x22.
What is the RISC-V assembly code for below:
```c
    A[12] = h + A[8];
```
Answer:
```assembly
    ld x9, 64(x22) // Temporary reg x9 gets A[8] (8*8 due to byte addressing)
    add x9, x21, x9 // adds up

    sd x9, 96(x22) // Stores h + A[8] back into A[12] (8*12)
```

Since there are limited numbers of registers, the compiler tries to keep the most frequently used variables in registers, and places the rest in memory. 
The process of putting less frequently used variables into memory is called **spilling** registers.

Registers take less time to access *and* have higher throughput than memory.
Why?
1. A RISC-V arithmetic instruction can read two registers, operate on them, and write the result. 
2. A RISC-V data transfer instruction only reads one operands or writes on operande, without operating on it.

To achieve the highest performance and conserve energy, an ISA must have enough registers, and compiliers must use registers efficiently.

Energy and performance of registers versus memory.
- 0.25 vs 50   ns
- 0.1  vs 1000 pJ

These large differences led to caches. (later)

## Constant or Immediate Operands

Many times a program will use a constant in an operations.
For example:
```assembly
    ld x9, AddrConstant4(x3) // x9 = constant 4
    add x22, x22, x9 // x22 = x22 + 4
```
Alternatives:
```assembly
    addi x22, x22, 4 // x22 = x22 + 4
```
This quick add instructions with one constant operand is called *add immediate* or *addi*.
This is much faster and efficient.

The constant zero is frequently used.
Hence, RISC-V dedicates register x0 to be hard-wired to the value zero.
For example, *sub* instruction with x0 can negate the value.
**common case fast**

NOTES:
The rate of increase in the number of registers in a chip over time doesn't follow Moore's Laws.
Since ISA determines viable number of registers, ISA must be updated.

NOTES:
In the past time,
```assembly
    ld x1, A(8) // A(8) -> offset(A) + register(8) (A is the address of array A)
```
Thus, base register(where (8)) is also called the *index register*.
Today's memories are much larger, so the base address (A) of the array is normally passed in register since it won't fit in the offset.
Now,
```assembly
    ld x1, 8(A)
```

NOTES:
The migration from 32-bit address computers to 64-bit address computers left compiler writers a choice of the size of data types in C.
They have different choices such as Microsoft Windows have 32 bits 'long int' types while Linux and Most Unix have 64 bits.


