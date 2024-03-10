#ifndef INC_8BIT_VM_VM_H
#define INC_8BIT_VM_VM_H

#include <stddef.h>
#include <stdint.h>

typedef uint8_t reg_t;
typedef uint8_t byte_t;

typedef struct {
    byte_t *bytes;
    size_t size;
} mem_t;

typedef struct {
    mem_t mem;
    reg_t reg[5];
    reg_t input;
    byte_t *pc;
} vm_t;

typedef enum {
    REG_0 = 0,
    REG_1 = 1,
    REG_2 = 2,
    REG_3 = 3,
    REG_4 = 4,
    IO = 5
} reg_id_t;

vm_t *vm_create(size_t mem_size);

void vm_run(vm_t *vm);

void vm_load(vm_t *vm, mem_t mem);

void vm_destroy(vm_t *vm);

#endif //INC_8BIT_VM_VM_H
