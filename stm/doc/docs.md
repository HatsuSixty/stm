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