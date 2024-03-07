#ifndef INC_8BIT_VM_VM_H
#define INC_8BIT_VM_VM_H

#include <stddef.h>
#include <stdint.h>

typedef uint8_t *mem_t;
typedef uint8_t reg_t;

typedef struct {
    mem_t mem;
    size_t mem_size;
    reg_t reg[5];
    reg_t input;
    mem_t pc;
} vm_t;

typedef enum {
    REG_0 = 0b000,
    REG_1 = 0b001,
    REG_2 = 0b010,
    REG_3 = 0b011,
    REG_4 = 0b100,
    IO = 0b101
} reg_id_t;

vm_t *vm_create(size_t mem_size);

void vm_run(vm_t *vm);

void vm_destroy(vm_t *vm);

#endif //INC_8BIT_VM_VM_H
