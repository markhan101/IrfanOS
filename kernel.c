#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "drivers/include/serial.h"
#include "drivers/include/vga.h"
#include "sys/include/gdt.h"
#include "sys/include/idt.h"
#include "sys/include/timer.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
	terminal_initialize();
	terminal_writestring("Welcome to Irfan0S!\n");

	init_serial();
	write_serial("SERIAL OUTPUT ENABLED...\n");
	//  TODO FIX ORDER CHANGE ISSUE
	INIT_GDT();
	// write_serial("GDT CONFIGURED AND ENABLED...\n");

	// INIT_IDT();
	// write_serial("IDT CONFIGURED AND ENABLED...\n");

	// INIT_ISR();
	// write_serial("ISR CONFIGURED AND ENABLED...\n");

	// INIT_IRQ();
	// write_serial("IRQ CONFIGURED AND ENABLED...\n");

	// INIT_TIMER();
	// write_serial("TIMER CONFIGURED AND ENABLED...\n");
}
