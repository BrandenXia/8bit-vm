#ifndef INC_8BIT_VM_OP_H
#define INC_8BIT_VM_OP_H

#include <stdbool.h>
#include <stdint.h>
#include "vm/vm.h"

typedef enum {
    INST_IMMEDIATE = 0,
    INST_COMPUTE = 1,
    INST_COPY = 2,
    INST_JUMP = 3
} inst_t;

typedef enum {
    COMPUTE_OR = 0,
    COMPUTE_NAND = 1,
    COMPUTE_NOR = 2,
    COMPUTE_AND = 3,
    COMPUTE_ADD = 4,
    COMPUTE_SUB = 5,
    COMPUTE_MUL = 6,
    COMPUTE_DIV = 7
} compute_op_t;

typedef enum {
    JUMP_NEVER = 0,
    JUMP_ZERO = 1,
    JUMP_NEG = 2,
    JUMP_NOT_POS = 3,
    JUMP_ALWAYS = 4,
    JUMP_NOT_ZERO = 5,
    JUMP_NOT_NEG = 6,
    JUMP_POS = 7
} jump_op_t;

typedef uint8_t opcode_t;

inst_t get_inst(opcode_t opcode);

compute_op_t get_compute_op(opcode_t opcode);

reg_t compute(compute_op_t op, reg_t a, reg_t b);

reg_id_t get_copy_src(opcode_t opcode);

reg_id_t get_copy_dst(opcode_t opcode);

jump_op_t get_jump_op(opcode_t opcode);

bool jump(jump_op_t op, reg_t reg);

#endif //INC_8BIT_VM_OP_H
