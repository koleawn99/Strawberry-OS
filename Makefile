# Define compilers and tools
CC = gcc
AS = nasm
LD = ld

# Compiler flags for bare-metal 32-bit development
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-pie -fno-pie
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# Define object files
OBJ = src/boot.o src/kernel.o

# Default target: build the kernel binary
all: strawberry_os.bin

# Compile assembly code
src/boot.o: src/boot.asm
	$(AS) $(ASFLAGS) src/boot.asm -o src/boot.o

# Compile C code
src/kernel.o: src/kernel.c
	$(CC) $(CFLAGS) -c src/kernel.c -o src/kernel.o

# Link everything together into the final OS binary
strawberry_os.bin: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o strawberry_os.bin

# Run the OS inside the QEMU emulator
run: strawberry_os.bin
	qemu-system-i386 -kernel strawberry_os.bin -display gtk

# Clean up compiled files
clean:
	rm -f src/*.o strawberry_os.bin
