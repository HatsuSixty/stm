# Docs

Official stm documentation.

## Basics

| Operator      | Function                                                                                                             |
|---------------|----------------------------------------------------------------------------------------------------------------------|
| `OP_PUTC`     | Print the character equivalent to the ascii code on the top of the stack, to stdout                                  |
| `OP_PUTI`     | Print an integer on the top of the stack to stdout                                                                   |
| `OP_PLUS`     | Remove 2 integers at the top of the stack, sum them up, and push the result back                                     |
| `OP_MINUS`    | Remove 2 integers at the top of the stack, subtract them, and push the result back                                   |
| `OP_MULT`     | Remove 2 integers at the top of the stack, multiply them, and oush the result back                                   |
| `OP_DIV`      | Remove 2 integers at the top of the stack, divide them, and push the result back                                     |
| `OP_MOD`      | Remove 2 integers at the top of the stack, divide them, and push the rest of the division back                       |
| `OP_PUSH_INT` | Push the operand (byte after the byte instruction) onto the stack                                                    |
| `OP_AT`       | Push the number at the position that the operand (byte after the byte instruction) indicates on the top of the stack |
| `OP_DROP`     | Remove the number on the top of the stack                                                                            |
| `OP_DUP`      | Duplicate the number on the top of the stack                                                                         |
| `OP_SWAP`     | Change the order of 2 numbers on the top of the stack                                                                |
| `OP_ROT`      | Change the order of 3 numbers on the top of the stack (1st -> 3st, 3st -> 1st)                                       |
| `OP_OVER`     | Push the 1st number on the stack onto top of the stack                                                               |

## Logic

| Operator     | Function                                                                                                                                            |
|--------------|-----------------------------------------------------------------------------------------------------------------------------------------------------|
| `OP_JMP`     | Jump to the instruction at the position that the operand (byte after the byte instruction) indicates                                                |
| `OP_JMP_IF`  | Jump to the instruction at the position that the operand (byte after the byte instruction) indicates if the number on the top of the stack is not 0 |
| `OP_EQU`     | Remove 2 integers at the top of the stack, compare and "see" if they equals, and push the result back                                               |
| `OP_LESS`    | Remove 2 integers at the top of the stack, compare and "see" if one is less than other, and push the result back                                    |
| `OP_GREATER` | Remove 2 integers at the top of the stack, compare and "see" if one is greater than other, and push the result back                                 |
| `OP_NOT`     | Remove 1 integer at the top of the stack, if the number is greater than 0, push number 0, else push number 1                                        |
| `OP_OR`      | Remove 2 integers at the top of the stack, if one or more of them is greater than 0, push 1                                                         |
| `OP_AND`     | Remove 2 integers at the top of the stack, if the 2 numbers are greater than 0, push 1, else, push 0                                                |

## Files

| Operator   | Function                                                                                 |
|------------|------------------------------------------------------------------------------------------|
| `OP_OPEN`  | Read the temporary buffer as a string and open the file that have the string as its path |
| `OP_CLOSE` | Close an opened file                                                                     |
| `OP_WRITE` | Read the temporary buffer as a string and write the string to the current opened file    |
| `OP_READ`  | Read the current opened file and write as a string to the temporary buffer               |
| `OP_PUT`   | Write the number on the top of the stack to the current opened file                      |

## General

| Operator   | Function                                                                         |
|------------|----------------------------------------------------------------------------------|
| `OP_RAND`  | Similar to rand() in C, pushes the result on the stack                           |
| `OP_PRINT` | Print the temporary buffer as a string                                           |
| `OP_NULL`  | It does nothing                                                                  |
| `OP_QUIT`  | Remove 1 integer at the top of the stack, and exit with the integer as exit code |

## Temporary buffer

The temporary buffer is used by the virtual machine to store strings and temporary data. The instructions to manipulate the temporary buffer are:
```
OP_TMP_PUSH_INT
OP_TMP_DROP
OP_NQDEBUG_TMP_BUFF
OP_TMP_AT
```

## Temporary array

Temporary array is not used by the virtual machine, it was made to let the users do whatever they want with this array. The instruction to manipulate the temporary array are:
```
OP_ARR_PUSH_INT
OP_ARR_DROP
OP_ARR_AT
OP_NQDEBUG_TMP_ARR
```
