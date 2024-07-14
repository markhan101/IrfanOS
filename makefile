# # #i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# # #i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

# Toolchain
CC = i686-elf-gcc
LD = i686-elf-gcc
AS = i686-elf-as

# Flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib
LIBS = -lgcc

# List of source files
SRCS = kernel.c serial.c vga.c gdt.c
OBJS = $(SRCS:.c=.o)
ASFLAGS =

# Directories
BIN_DIR = bin
DRIVERS_DIR = drivers
SYS_DIR = sys

# Source files
KERNEL_SRC = kernel.c
DRIVERS_SRC = $(DRIVERS_DIR)/serial.c $(DRIVERS_DIR)/vga.c
SYS_SRC = $(SYS_DIR)/gdt.c

# Object files
KERNEL_OBJ = $(BIN_DIR)/kernel.o
DRIVERS_OBJ = $(BIN_DIR)/serial.o $(BIN_DIR)/vga.o
SYS_OBJ = $(BIN_DIR)/gdt.o
BOOT_OBJ = $(BIN_DIR)/boot.o

# All object files
OBJS = $(BOOT_OBJ) $(KERNEL_OBJ) $(DRIVERS_OBJ) $(SYS_OBJ)

# Binary output
BIN = myos.bin

# Phony targets
.PHONY: all clean

# Default target
all: $(BIN_DIR)/$(BIN)

# Link the kernel
$(BIN_DIR)/$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -lgcc

# Compile the kernel
$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the drivers
$(BIN_DIR)/serial.o: $(DRIVERS_DIR)/serial.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/vga.o: $(DRIVERS_DIR)/vga.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the system files
$(BIN_DIR)/gdt.o: $(SYS_DIR)/gdt.c
	$(CC) $(CFLAGS) -c $< -o $@


# gdt.o: gdt.c
	$(CC) $(CFLAGS) -c $< -o $@

#gdt.o depends on gdt.c and a function in gdt.c depends on gdt.s

gdt.o: gdt.c gdt.s
	$(CC) $(CFLAGS) -c $< -o $@



# Assemble boot.s
$(BOOT_OBJ): boot.s
	$(AS) $(ASFLAGS) $< -o $@

# Clean up


clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/$(BIN)
