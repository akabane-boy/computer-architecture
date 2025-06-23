# Logical Operations

The first computers operated on full words.
It soon became clear that it was useful to operate on fields of bits within a word or even on individual bits.
Examining characters (1 byte) within a word is one example of such an operation.
It follows that operations were added to programming languages and ISA to simplify the packing and unpacking of bits into words. These instructions are called **logical operations**.

## Shifts

### shift left logical immediate (slli)
shift left by 4:

00000000 00000000 00000000 00000000 00000000 000000000 00000000 00001001 = 9

00000000 00000000 00000000 00000000 00000000 000000000 00000000 10010000 = 144

```assembly
    slli x11, x19, 4 // reg x11 = reg x19 << 4 bits
```

These shift instructions use the *I-type* format.

Since it isn't useful to shift a 64-bit register by more than 63 bits, only the lower 6 bits of the I-type format's 12-bit immediate are actually used. The remaining 6 bits are repurposed as an additional opcode field, funct6.

|funct6|immediate|rs1|funct3|rd|opcode|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|0|4|19|1|11|19|

#### Shifting left by *i* bits gives the identical result as multiplying by $2^{i}$ , just as shifting a decimal number by *i* digits is equivalent to multiplying by 10*i*.

### shift right logical immediate (srli)
Same with slli

### shift right arithmetic (srai)
Similar to *srli*, except rather than filling the vacated bits on the left with zeros, it fills them with copies of the old sign bit.

## AND
A logical bit-by-bit operation with two operands that calculates a 1 only if there is a 1 in *both* operands.

### Example:
Register x11 contains:

00000000 00000000 00000000 00000000 00000000 00000000 00001101 11000000

Register x10 contains:

00000000 00000000 00000000 00000000 00000000 00000000 00111100 00000000

then after
```assembly
and x9, x10, x11 // reg x9 = reg x10 & reg x11
```

the value of register x9 would be

00000000 00000000 00000000 000000000 00000000 00000000 00001100 00000000

Such a bit pattern in conjunction with AND is traditionally called a *mask*, since the mask "conceals" some bits.

## OR
A logical bit-by-bit operation with two operands that calculates a 1 if there is a 1 in *either* operand.

### Example:
Register x11 contains:

00000000 00000000 00000000 00000000 00000000 00000000 00001101 11000000

Register x10 contains:

00000000 00000000 00000000 00000000 00000000 00000000 00111100 00000000

```assembly
or x9, x10, x11 // reg x9 = reg x10 | reg x11
```

the value of register x9 would be

00000000 00000000 00000000 00000000 00000000 00000000 00111101 11000000

## NOT
A logical bit-by-bit operation with one operand that inverts the bits; that is, it replaces every 1 with a 0, and every 0 with a 1.

## XOR
A logical bit-by-bit operation with two operands that calculates the exclusive OR of the two operands. That is, it calculates a 1 only if the values are different in the two operands.

The designers of RISC-V decided to include the instruction **XOR** instead of NOT. Because the equivalent to NOT is and XOR with 111...111.

### Example:
Register x12 contains:

00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000

Register x10 contains:

00000000 00000000 00000000 00000000 00000000 00000000 00111100 00000000

```assembly
xor x9, x10, x12 // reg x9 = reg x10 ^ reg x12
```

the value of register x9 would be

00000000 00000000 00000000 00000000 00000000 00000000 00111100 00000000

### NOTE:
Constants are useful in logical operations as well as arithmetic operations.
So RISC-V provides the instructions *and immediate* (andi), *or immediate* (ori), and *exclusive or immediate* (xori).

## NOTE:
C allows *bit fields* or *fields* to be defined within doublewords, both 
1. allowing objects to be packed within a doubleword and 
2. to match an externally enforced interface such as an I/O device.

All fields must fit within a single doubleword.
Fields are unsigned integers that can be as short as 1 bit.
C compiler insert and extract fields using logical instructions in RISC-V.


## NOTE:
Which operations can isolate a field in a doubleword?
1. AND
2. A shift left followed by a shift right

Answer: Both.












