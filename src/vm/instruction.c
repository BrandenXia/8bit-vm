#include <stdbool.h>
#include "vm/instruction.h"

inst_t get_inst(opcode_t opcode) {
    return (inst_t) (opcode >> 6); // move 6 bits to get the first 2 bits
}

compute_op_t get_compute_op(opcode_t opcode) {
    return (compute_op_t) (opcode & 0x07);  // 0x07 is 00000111
}

reg_t compute(compute_op_t op, reg_t a, reg_t b) {
    switch (op) {
        case COMPUTE_OR:
            return a | b;
        case COMPUTE_NAND:
            return ~(a & b);
        case COMPUTE_NOR:
            return ~(a | b);
        case COMPUTE_AND:
            return a & b;
        case COMPUTE_ADD:
            return a + b;
        case COMPUTE_SUB:
            return a - b;
        case COMPUTE_MUL:
            return a * b;
        case COMPUTE_DIV:
            return a / b;
    }
    return 0;
}

reg_id_t get_copy_src(opcode_t opcode) {
    return (reg_id_t) ((opcode >> 3) & 0x07);  // 0x07 is 00000111
}

reg_id_t get_copy_dst(opcode_t opcode) {
    return (reg_id_t) (opcode & 0x07);  // 0x07 is 00000111
}

jump_op_t get_jump_op(opcode_t opcode) {
    return (jump_op_t) (opcode & 0x07);  // 0x07 is 00000111
}

bool jump(jump_op_t op, reg_t reg) {
    switch (op) {
        case JUMP_NEVER:
            return false;
        case JUMP_ZERO:
            return reg == 0;
        case JUMP_NEG:
            return reg < 0;
        case JUMP_NOT_POS:
            return reg <= 0;
        case JUMP_ALWAYS:
            return true;
        case JUMP_NOT_ZERO:
            return reg != 0;
        case JUMP_NOT_NEG:
            return reg >= 0;
        case JUMP_POS:
            return reg > 0;
    }
    return false;
}
