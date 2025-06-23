# Signed and Unsigned Numbers

**binary digit**: Also called *bits*.
**least significant bit**: The rightmost bit in an RISC-V doubleword. bit 0.
**most significant bit**: The leftmost bit in an RISC-V doubleword. bit 63.

The RISC-V doubleword is 64-bits long, so we can represent $2^{64}$ different 64-bit patterns.
0 to $2^{64}-1$.

$$00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000$$
This is 8 bytes, 64 bits.

64-bit binary numbers can be represented as:

$$x_{63} * 2^{63} + x_{62} * 2^{62} + ... + x_{0} * 2^{0}$$

These $x_{i}$ 's are called **unsigned numbers**.

If the result of operations such as addition, subtraction, etc. cannot be represented by these rightmost hardware bits, *overflow* is said to be occured.

For the representation of negative number, we can add sign in a single bit;
the name for this representation is *sign and magnitude*.
But it has several shortcomings.
1. It's not obvious where to put the sign bit.
2. adders for sign and magnitude may need an extra step to set the sign.
3. has both a positive and negative zero.

Thus, sign and magnitude was soon abandoned.

## Two's complement

Better alternative, the final solution was: leading 0s mean positive, and leading 1s mean negative. *Two's complement*.

Example:

00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 = $0_{ten}$

00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001 = $1_{ten}$

00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010 = $2_{ten}$

...

01111111 11111111 11111111 11111111 11111111 11111111 11111111 11111101 = $9,223,372,036,854,775,805_{ten}$

01111111 11111111 11111111 11111111 11111111 11111111 11111111 11111110 = $9,223,372,036,854,775,806_{ten}$

01111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 = $9,223,372,036,854,775,807_{ten}$

10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 = $-9,223,372,036,854,775,808_{ten}$

10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001 = $-9,223,372,036,854,775,807_{ten}$

10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010 = $-9,223,372,036,854,775,806_{ten}$

...

11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111101 = $-3_{ten}$

11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111110 = $-2_{ten}$

11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 = $-1_{ten}$

Two's complement representation has the advantage that all negative numbers have a 1 in the MSB. Also, this bit is often called the *sign bit*.

Thus, we can represent positive and negative 64-bit numbers:

$$(x_{63} * -2^{63}) + (x_{62} * 2^{62}) + ... + (x_{1} * 2^{1}) + (x_{0} * 2^{0})$$

Overflow occurs when the sign bit is incorrect.

### NOTE:
Signed versus unsigned applies to *loads* as well as to *arithmetic*.

The function of a **signed load** is to copy the sign repeatedly to fill the rest of the register, called *sign extension*.
Unsigned loads simply fill with 0s to the left of the data.

RISC-V does offer two flavors of byte loads:
1. **load byte unsigned(lbu)** treats the byte as an unsigned number and thus zero-extends to fill the leftmost bits of the register.
2. **load byte(lb)** works with signed integers.

C programs almost always use bytes to represent characters, lbu is used pratically for byte loads.

### NOTE:
For example, memory addresses naturally start at 0 and continue to the largest address.
Thus, programs want to deal with both positive/negative and positive cases.
C, for example, names the *integers* (long long int) and the *unsigned integers* (unsigned long long int).

## Two useful shortcuts when working with two's complemnt
First:
Since $x+\bar{x}=-1$, therefore $\bar{x}+1=-x$.

Invert every 0 to 1 and every 0 to 1, then add one to the result.

Next:
Our next shortcut tells us how to convert a binary number represented in n bits to a number represented with more than n bits.
This shortcut is commonly called *sign extension*.

Take the msb from the smaller quantity, the sign bit, and replicate it to fill the new bits of the larger quantity.
The old nonsign bits are simply copied into the right portion of the new doubleword.

### Example:(Sign Extension Shortcut)
Convert 16-bit binary versions of $2_{ten}$ and $-2_{ten}$ to 64-bit binary numbers.

00000000 00000010 = 2

It is converted to a 64-bit number by making 48 copies of 0.

00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010 = 2

Let's negate the 16-bit version of 2

0000 0000 0000 0010 becomes,

1111 1111 1111 1101 + 1 = 1111 1111 1111 1110

Then,

11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111110 = -2

## Summary
The main point of this section is that we need to represent both positive and negative integers within a computer, and although there are pros and cons to any option, the unanimous choice since 1965 has been two's complement.

### NOTE:
Two's complement gets its name from the rule that the unsigned sum of an n-bit number and its n-bit negative is $2^{n}$.

## One's Complement
The most negative value by 100...000.

The most positive value by 011...111.

The inversion of every bit in a pattern: 0 to 1 and 1 to 0.

It has two zeros, equal number of negatives and positives.

## Biased Notation
The most negative value by 000...000.

The most positive value by 111...111.

with 0 typically having the value 100...000.

