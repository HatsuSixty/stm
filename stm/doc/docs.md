# Docs

Official stm documentation.

## Basics

| Operator      | Function                                                                           |
|---------------|------------------------------------------------------------------------------------|
| `OP_PUTC`     | Print the character equivalent to the ascii code on the top of the stack to stdout |
| `OP_PUTI`     | Print an integer on the top of the stack to stdout                                 |
| `OP_PLUS`     | Remove 2 integers on the top of the stack, sum them up, and push the result back   |
| `OP_MINUS`    | Remove 2 integers on the top of the stack, subtract them, and push the result back |
| `OP_MULT`     | Remove 2 integers on the top of the stack, multiply them, and oush the result back |
| `OP_DIV`      | Remove 2 integers on the top of the stack, divide them, and push the result back   |
| `OP_PUSH_INT` | Put the number (byte) after the byte that represents the operator to the stack     |
| `OP_DROP`     | Remove the number on the top of the stack                                          |
| `OP_DUP`      | Duplicate the number on the top of the stack                                       |
| `OP_SWAP`     | Change the order of 2 numbers on the top of the stack                              |
| `OP_ROT`      | Change the order of 3 numbers on the top of the stack (1st -> 3st, 3st -> 1st)     |
| `OP_OVER`     | Push the 1st number on the stack on the top of the stack                           |
