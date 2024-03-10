#include "vm/vm.h"
#include "compiler/compiler.h"

int main(void) {
    const char *source = "IMMEDIATE 10\nCOPY 0 IO\n";
    mem_t mem = compile(source);
    vm_t *vm = vm_create(0x800);
    vm_load(vm, mem);
    vm_run(vm);
}
