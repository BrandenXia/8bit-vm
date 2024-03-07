#include "vm/vm.h"

int main(void) {
    vm_t *vm = vm_create(0x800);
    vm->mem[0] = 0b10101000;
    vm->mem[1] = 0b10000101;
    vm_run(vm);
    vm_destroy(vm);
    return 0;
}
