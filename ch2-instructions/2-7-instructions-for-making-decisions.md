# Instructions for Making Decisions
----
RISC-V assembly language includes *two* decision-making instructions, similar to an *if* statement with a *go to*.

## Conditional Statement
----

### The first instruction beq
```assembly
beq rs1, rs2, L1
```
This instructions means go to the statement labeled L1 if the value in register *rs1* **equals** the value in register *rs2*.

The *beq* stands for *branch if equal*.

### The second instruction bnq
```assembly
bne rs1, rs2, L1
```
It means go to the statement labeled L1 if the value in register rs1 does *not equal* the value in register rs2.

The *bne* stands for *branch if not equal*.

These two instructions are traditionally called **conditional branches**.

**conditional branches**:
An instruction that tests a value and that allows for a subsequent transfer of control to a new address in the program based on the outcome of the test.

### Example:(Compiling if-then-else into Conditional Branches)
In the following code segment, f, g, h, i, and j are variables.
If the five variables f through j correspond to the five registers x19 through x23, what is the compiled RISC-V code for this C *if* statement?

```c
if (i == j) 
    f = g + h; 
else
    f = g - h;
```

#### Answer
It would seem that we would want to branch if i and j are equal (beq).
In general, the code will be more efficient if we test for the opposite condition.
Here is the code:
```assembly
bne x22, x23, Else // go to Else if i != j (i == x22, j == x23)
add x19, x20, x21 // f = g + h (skipped if i != j)
```
We now need to go to the end of the *if* statement.
This example introduces **unconditional branch**.
The processor always follows the branch.
```assembly
beq x0, x0, Exit // if 0 == 0, go to Exit
```
The assignment statement in the *else* portion of the *if* statement can again be compiled into a single instruction.
We also need to label Else.
```assembly
Else:sub x19, x20, x21 // f = g - h
Exit:
```
So, the whole assembly would be:
```assembly
// f == x19, g == x20, h == x21, i == x22, j == x23
bne x22, x23, Else // go to Else if i != j
add x19, x20, x21 // f = g + h (skipped if i != j)
beq x0, x0, Exit // if 0 == 0, go to Exit
Else:sub x19, x20, x21 // f = g - h (skipped if i == j)
Exit:
```

### NOTE:
Notice that the assembler relieves the compiler and the assembly language programmer from the tedium of calculating addresses for branches.

### NOTE:
Compilers frequently create branches and labels where they do not appear in the programming language.
This is one benefit of writing in high-level programming languages.

## Loops
----

### Example:(Compiling a while Loop in C)
Here is a traditional loop in C:
```c
while (save[i] == k)
    i += 1;
```
Assume that i and k correspond to registers x22 and x24 and the base of the array save is in x25.
What is the RISC-V assembly code corresponding to this C code?

#### Answer:
The first step is to load save[i] into a temporary register.

We need its address.
Since multiplying 8 is equivalent to shifting left by 3 bits.
```assembly
Loop: slli x10, x22, 3 // Temp reg x10 = i * 8
```
To get the address of save[i], we need to add x10 and the base of save in x25:
```assembly
add x10, x10, x25 // x10 = i*8 (x10) + address of save[0] (x25)
```
Now we can use that address to load save[i] into a temporary register.
```assembly
ld x9, 0(x10) // Temp reg x9 = save[i]
```
The next instruction performs the loop test, exiting if save[i] != k:
```assembly
bne x9, x24, Exit // go to Exit if save[i] != k
```
The following instruction adds 1 to i:
```assembly
addi x22, x22, 1 // i = i + 1
```
The end of the loop branches back to the while test.
We just add the the Exit label after it, and we're done.
```assembly
beq x0, x0, Loop // go to Loop
Exit:
```

### NOTE:
**basic block**: 
A sequence of instructions without branches (except possibly at the end) and without branch targets or branch labels (except possibly at the beginning).

*branch to branch*

## Another test
There are many other relationships between two numbers.

For example, a *for* loop may want to test to see if the index variable is less than 0.
The full set of comparisons is:

- less than (<)
- less than or equal (<=)
- greater than (>)
- greater than or equal (>)
- equal (=)
- not equal (!=)

Comparison of bit patterns must deal with the dichotomy between
signed and unsigned numbers.

RISC-V provides instructions that handle both cases.

*blt*: "branch if less than" compares the values in rs1 and rs2 and takes the branch 
if the value in rs1 is smaller, when they are treated as two's complement.

*bge*: "branch if greater than or equal" is the exact opposite case.

*bltu*: "branch if less than, unsigned"

*bgeu*: "branch if greater than or equal, unsigned"

#### MIPS
Set a register based upon the result of the comparison,
then branch on the value in that temporary register with the *beq* or *bne* instructions.

This approach can make the processor datapath slightly simpler,
but it takes more instructions to express a program.

#### ARM
Keep extra bits that record what occurred during an instruction.

These additional bits, called *condition codes* or *flags*, indicate,
for example, if the result of an arithmetic operation was negative, or zero, or
resulted in overflow.

Conditional branches then use combinations of these condition codes to perform the desired test.

If many instructions always set them, it will create dependencies that will make it
difficult for pipelined execution (Chapter 4)

## Bounds Check Shortcut
----
Treating signed numbers as if they were unsigned gives us a low-cost way of checking if
0 <= x < y, which matches the index out-of-bounds check for arrays.

An unsigned comparison of x < y checks if x is negative as well as if x is less than y.

### Example
Use this shortcut to reduce an index-out-of-bounds check:
branch to *IndexOutOfBounds* if x20 >= x11 or if x20 is negative.

### Answer
The checking code just uses unsigned greater than or equal to do both checks:
```assembly
bgeu x20, x11, IndexOutOfBounds // if x20 >= x11 or x20 <0,
                                // go to IndexOutOfBounds
```

What here saying is, x11 has the array's length and x20 needs to be checked.

x20 should not greater than or equal to x11 as well as should not be negative.

Hence, *bgeu* can check those two cases in one instruction.

## Case/Switch Statement
----
**branch address table** 
Also called **branch table**. A table of addresses of alternative instruction sequences.

The simplest way to implement *switch* is via a sequence of conditional tests (if-else chain)

To be more efficient, the program needs only to index into the branch table
and then branch to the appropriate sequence.

The branch table is just an array of doublewords containing addresses that correspond to labels
in the code.

In RISC-V, the jump-and-link register instruction (*jalr*) serves this purpose.

### NOTES:
Although there are many statements for decisions and loops in programming languages
like C and Java, the bedrock statement that implements them at the instruction set level
is the **conditional branch**.











