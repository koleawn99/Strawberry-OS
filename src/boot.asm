; Declare constants for the Multiboot header
MODULEALIGN equ  1 << 0             ; align loaded modules on page boundaries
MEMINFO     equ  1 << 1             ; provide memory map
MAGIC       equ  0x1BADB002         ; 'magic number' lets bootloader find the header
FLAGS       equ  MODULEALIGN | MEMINFO
CHECKSUM    equ -(MAGIC + FLAGS)    ; checksum of above, to prove we are multiboot

; Define the Multiboot section based on our linker script
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Allocate space for a small temporary stack for our C kernel
section .bss
align 16
stack_bottom:
    resb 16384 ; Reserve 16 Kilobytes of space for the stack
stack_top:

; The entry point defined in our linker script
section .text
global start
start:
    ; Set up the stack pointer register (esp)
    mov esp, stack_top

    ; Call our kernel's main function (which we will write next in C)
    extern kernel_main
    call kernel_main

    ; If the kernel ever returns, lock the CPU in an infinite loop
.hang:
    cli      ; Clear interrupts (stop keyboard/timers from waking CPU)
    hlt      ; Halt the CPU
    jmp .hang ; If something wakes it up anyway, jump back and halt again
