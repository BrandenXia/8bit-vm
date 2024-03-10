#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "vm/vm.h"
#include "vm/instruction.h"

vm_t *vm_create(size_t mem_size) {
    assert(mem_size > 0);

    vm_t *vm = malloc(sizeof(vm_t));
    vm->mem.bytes = calloc(mem_size, sizeof(byte_t));
    vm->mem.size = mem_size;
    vm->pc = vm->mem.bytes;
    return vm;
}

void vm_run(vm_t *vm) {
    for (;vm->pc < vm->mem.bytes + vm->mem.size; vm->pc++) {
        opcode_t opcode = *vm->pc;
        inst_t inst = get_inst(opcode);
        switch (inst) {
            case INST_IMMEDIATE:
                vm->reg[0] = opcode & 0x3F; // 0x3F is 00111111
                break;
            case INST_COMPUTE: {
                compute_op_t op = get_compute_op(opcode);
                reg_t a = vm->reg[1];
                reg_t b = vm->reg[2];
                vm->reg[3] = compute(op, a, b);
                break;
            }
            case INST_COPY: {
                reg_id_t src_id = get_copy_src(opcode);
                reg_id_t dst_id = get_copy_dst(opcode);

                reg_t *src, *dst;

                if (src_id == IO) {
                    char input[128];
                    scanf("%s", input);
                    vm->input = strtoul(input, NULL, 0);
                    src = &vm->input;
                } else {
                    src = &vm->reg[src_id];
                }

                if (dst_id == IO) {
                    printf("%d\n", *src);
                    break;
                } else {
                    dst = &vm->reg[dst_id];
                }

                *dst = *src;
            }
            case INST_JUMP: {
                jump_op_t op = get_jump_op(opcode);
                bool cond = jump(op, vm->reg[3]);
                if (cond) vm->pc = vm->mem.bytes + vm->reg[0] - 1;
                break;
            }
        }
    }
}

void vm_load(vm_t *vm, mem_t mem) {
    if (vm->mem.size < mem.size) {
        free(vm->mem.bytes);
        vm->mem.bytes = calloc(mem.size, sizeof(byte_t));
        vm->mem.size = mem.size;
    }

    memcpy(vm->mem.bytes, mem.bytes, mem.size);
}

void vm_destroy(vm_t *vm) {
    free(vm->mem.bytes);
    free(vm);
}
