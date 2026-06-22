ENTRY(start)

SECTIONS
{
    /* The Multiboot standard requires the kernel to be loaded at 1MB */
    . = 1M;

    /* First, we put the boot code containing the magic header */
    .text :
    {
        *(.multiboot)
        *(.text)
    }

    /* Read-only data */
    .rodata :
    {
        *(.rodata)
    }

    /* Initialized data */
    .data :
    {
        *(.data)
    }

    /* Uninitialized data (stack goes here) */
    .bss :
    {
        *(.bss)
    }
}
