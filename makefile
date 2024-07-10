# #i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# #i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc


# CC = i686-elf-gcc
# LD = i686-elf-gcc
# CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib
# LIBS = -lgcc

# # List of source files
# SRCS = kernel.c serial.c
# OBJS = $(SRCS:.c=.o)

# # Default target
# all: myos.bin

# kernel.o: kernel.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# serial.o: serial.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# boot.o: boot.s
# 	$(CC) -c $< -o $@ $(CFLAGS)

# myos.bin: boot.o $(OBJS)
# 	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

# clean:
# 	rm -f *.o myos.bin


CC = i686-elf-gcc
LD = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib
LIBS = -lgcc

# List of source files
SRCS = kernel.c serial.c vga.c
OBJS = $(SRCS:.c=.o)

# Default target
all: myos.bin

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

serial.o: serial.c
	$(CC) $(CFLAGS) -c $< -o $@

vga.o: vga.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.o: boot.s
	$(CC) -c $< -o $@ $(CFLAGS)

myos.bin: boot.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f *.o myos.bin


