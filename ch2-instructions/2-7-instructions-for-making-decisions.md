# Instructions for Making Decisions
RISC-V assembly language includes *two* decision-making instructions, similar to an *if* statement with a *go to*.

## Conditional Statement

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
TODO: From HERE! 6/23/2025

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
















