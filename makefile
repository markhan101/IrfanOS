# #qemu-system-i386 -kernel bin/myos.bin -d int -serial stdio
# #run command

# CC = i686-elf-gcc
# LD = i686-elf-gcc
# AS = i686-elf-as

# # Flags
# CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib
# LIBS = -lgcc

# # Directories
# BIN_DIR = bin
# DRIVERS_DIR = drivers
# SYS_DIR = sys
# UTILS_DIR = utils

# # Source files
# KERNEL_SRC = kernel.c
# DRIVERS_SRC = $(DRIVERS_DIR)/serial.c $(DRIVERS_DIR)/vga.c
# SYS_SRC = $(SYS_DIR)/gdt.c $(SYS_DIR)/idt.c $(SYS_DIR)/timer.c
# UTILS_SRC = $(UTILS_DIR)/io.c $(UTILS_DIR)/string.c

# # Assembly source files
# SYS_ASM_SRC = $(SYS_DIR)/gdt.s $(SYS_DIR)/idt.s

# # Object files
# KERNEL_OBJ = $(BIN_DIR)/kernel.o
# DRIVERS_OBJ = $(BIN_DIR)/serial.o $(BIN_DIR)/vga.o
# SYS_OBJ = $(BIN_DIR)/gdt.o $(BIN_DIR)/gdts.o $(BIN_DIR)/idt.o $(BIN_DIR)/idts.o $(BIN_DIR)/timer.o
# UTILS_OBJ = $(BIN_DIR)/io.o $(BIN_DIR)/string.o
# BOOT_OBJ = $(BIN_DIR)/boot.o

# # All object files
# OBJS = $(BOOT_OBJ) $(KERNEL_OBJ) $(DRIVERS_OBJ) $(SYS_OBJ) $(UTILS_OBJ)

# # Binary output
# BIN = myos.bin

# # Phony targets
# .PHONY: all clean

# # Default target
# all: $(BIN_DIR)/$(BIN)

# # Link the kernel
# $(BIN_DIR)/$(BIN): $(OBJS)
# 	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

# # Compile the kernel
# $(KERNEL_OBJ): $(KERNEL_SRC)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Compile the drivers
# $(BIN_DIR)/serial.o: $(DRIVERS_DIR)/serial.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(BIN_DIR)/vga.o: $(DRIVERS_DIR)/vga.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Compile the system files
# $(BIN_DIR)/gdt.o: $(SYS_DIR)/gdt.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(BIN_DIR)/idt.o: $(SYS_DIR)/idt.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(BIN_DIR)/timer.o: $(SYS_DIR)/timer.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Assemble the system assembly files
# $(BIN_DIR)/gdts.o: $(SYS_DIR)/gdt.s
# 	$(AS) $(ASFLAGS) $< -o $@

# $(BIN_DIR)/idts.o: $(SYS_DIR)/idt.s
# 	$(AS) $(ASFLAGS) $< -o $@

# # Compile the utility files
# $(BIN_DIR)/io.o: $(UTILS_DIR)/io.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(BIN_DIR)/string.o: $(UTILS_DIR)/string.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Assemble boot.s
# $(BOOT_OBJ): boot.s
# 	$(AS) $(ASFLAGS) $< -o $@

# # Clean up
# clean:
# 	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/$(BIN)

# # Run QEMU
# run: all
# 	qemu-system-i386 -kernel $(BIN_DIR)/$(BIN) -d int -serial stdio

#--------------------------------------------------

#gdt issue make

# Specify the compiler
CC = i686-elf-gcc

# Specify the flags for compilation
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Specify the linker flags
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

# Target to build all
all: bin/myos.bin

# Rule to build the kernel binary
bin/myos.bin: bin/kernel.o bin/serial.o bin/vga.o bin/string.o bin/gdt.o bin/io.o bin/boot.o
	$(CC) $(LDFLAGS) -o bin/myos.bin bin/kernel.o bin/serial.o bin/string.o bin/vga.o bin/gdt.o bin/io.o bin/boot.o

# Rule to compile kernel.c
bin/kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o bin/kernel.o

# Rule to compile serial.c
bin/serial.o: drivers/serial.c
	$(CC) $(CFLAGS) -c drivers/serial.c -o bin/serial.o

# Rule to compile string.c
bin/string.o: utils/string.c
	$(CC) $(CFLAGS) -c utils/string.c -o bin/string.o

# Rule to compile vga.c
bin/vga.o: drivers/vga.c
	$(CC) $(CFLAGS) -c drivers/vga.c -o bin/vga.o

# Rule to compile gdt.c
bin/gdt.o: sys/gdt.c
	$(CC) $(CFLAGS) -c sys/gdt.c -o bin/gdt.o

# Rule to compile io.c
bin/io.o: utils/io.c
	$(CC) $(CFLAGS) -c utils/io.c -o bin/io.o

# Rule to Assembly boot.s
bin/boot.o: boot.s
	i686-elf-as boot.s -o bin/boot.o


# Clean up build files
clean:
	rm -f bin/*.o bin/myos.bin

# Phony targets
.PHONY: all clean



