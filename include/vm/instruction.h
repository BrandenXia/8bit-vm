#ifndef INC_8BIT_VM_OP_H
#define INC_8BIT_VM_OP_H

#include <stdint.h>
#include "vm/vm.h"

typedef enum {
    INST_IMMEDIATE = 0b00,
    INST_COMPUTE = 0b01,
    INST_COPY = 0b10,
    INST_JUMP = 0b11
} inst_t;

typedef enum {
    COMPUTE_OR = 0b000,
    COMPUTE_NAND = 0b001,
    COMPUTE_NOR = 0b010,
    COMPUTE_AND = 0b011,
    COMPUTE_ADD = 0b100,
    COMPUTE_SUB = 0b101,
    COMPUTE_MUL = 0b110,
    COMPUTE_DIV = 0b111
} compute_op_t;

typedef enum {
    JUMP_NEVER = 0b000,
    JUMP_ZERO = 0b001,
    JUMP_NEG = 0b010,
    JUMP_NOT_POS = 0b011,
    JUMP_ALWAYS = 0b100,
    JUMP_NOT_ZERO = 0b101,
    JUMP_NOT_NEG = 0b110,
    JUMP_POS = 0b111
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
