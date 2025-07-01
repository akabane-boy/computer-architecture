# Supporting Procedures in Computer Hardware
----

**procedure**:
A stored subroutine that performs a specific task based on the parameters
with which it is provided. (function)

**abstraction**

In the execution of a procedure, the program must follow these six steps:

1. Put parameters in a place where the procedure can access them.
2. Transfer control to the procedure.
3. Acquire the storage resources needed for the procedure.
4. Perform the desired task.
5. Put the result value in a place where the calling program can access it.
6. Return control to the point of origin, since a procedure can be called from
several points in a program.

RISC-V's convention for procedure calling in allocating its 32 registers:

- x10 - x17: eight parameter register to return to the point of origin.
- x1: one return address register to return to the point of origin.

In addition, RISC-V assembly language includes an instruction just for the procedures:

it branches to an address and simultaneously save the address of the following
instruction to the destination register rd.

The **jump-and-link instruction**
```assembly
jal x1, ProcedureAddress // jump to ProcedureAddress and write return address to x1
```

**jump-and-link instruction**:
An instruction that branches to an address and simultaneously saves the address of the
following instruction in a register (usually x1 in RISC-V)

This "link", stored in register x1, is called the **return address*.
This is important because the same procedure could be called from several parts of
the program.

**return address**:
A link to the calling site that allows a procedure to return to the proper address;
in RISC-V it is stored in register x1.





