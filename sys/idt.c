// #include "include/idt.h"

// __attribute__((aligned(0x10))) static IDT_Entry IDT[IDT_SIZE];

// static IDT_Locator IDT_ptr;

// static void (*irq_handlers[16])();

// __attribute__((noreturn)) void EXCEPTION_HANDLER(char *msg)
// {
//     __asm__ volatile("cli");
//     write_serial("EXCEPTION: ");
//     write_serial(msg);
//     write_serial("\n");
//     __asm__ volatile("hlt");
// }

// __attribute__((noreturn)) void EXCEPTION_HANDLER_WITH_ERR_CODE(char *msg, uint32_t err_code)
// {
//     __asm__ volatile("cli");
//     write_serial("EXCEPTION: ");
//     write_serial(msg);
//     write_serial(" Error code: ");
//     write_serial_hex(err_code);
//     write_serial("\n");
//     __asm__ volatile("hlt");
// }

// void IDT_SET_DESCRIPTOR(uint8_t vector, void *isr, uint8_t flags)
// {

//     IDT[vector].base_low = (uint32_t)isr & 0xFFFF;
//     IDT[vector].selector = GDT_CODE_SEGMENT;
//     IDT[vector].zero = 0;
//     IDT[vector].flags = flags;
//     IDT[vector].base_high = (uint32_t)isr >> 16;
// }

// static bool vectors[IDT_SIZE] = {false};

// void exception(uint8_t vector)
// {
//     __asm__ volatile("cli");
//     write_serial("EXCEPTION: ");
//     write_serial_hex(vector);
//     write_serial("\n");
//     __asm__ volatile("hlt");
// }

// extern void *isr_stub_table[];

// __attribute__((naked)) static void exception_handler_0x00(void)
// {
//     exception(0x00);
// }

// __attribute__((naked)) static void exception_handler_0x01(void)
// {
//     exception(0x01);
// }

// __attribute__((naked)) static void exception_handler_0x02(void)
// {
//     exception(0x02);
// }

// __attribute__((naked)) static void exception_handler_0x03(void)
// {
//     exception(0x03);
// }

// __attribute__((naked)) static void exception_handler_0x04(void)
// {
//     exception(0x04);
// }

// __attribute__((naked)) static void exception_handler_0x05(void)
// {
//     exception(0x05);
// }

// __attribute__((naked)) static void exception_handler_0x06(void)
// {
//     exception(0x06);
// }

// __attribute__((naked)) static void exception_handler_0x07(void)
// {
//     exception(0x07);
// }

// __attribute__((naked)) static void exception_handler_0x08(void)
// {
//     __asm__(
//         "push 0x08\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x09(void)
// {
//     exception(0x09);
// }

// __attribute__((naked)) static void exception_handler_0x0a(void)
// {
//     __asm__(
//         "push 0x0a\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0b(void)
// {
//     __asm__(
//         "push 0x0b\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0c(void)
// {
//     __asm__(
//         "push 0x0c\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0d(void)
// {
//     __asm__(
//         "push 0x0d\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0e(void)
// {
//     __asm__(
//         "push 0x0e\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x10(void)
// {
//     exception(0x10);
// }

// __attribute__((naked)) static void exception_handler_0x11(void)
// {
//     __asm__(
//         "push 0x11\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x12(void)
// {
//     exception(0x12);
// }

// __attribute__((naked)) static void exception_handler_0x13(void)
// {
//     exception(0x13);
// }

// __attribute__((naked)) static void set_segment_regs_if_needed(void)
// {
//     __asm__(
//         "cmp DWORD PTR [esp + 8], 0x1b;"
//         "jne 1f;"
//         "push eax;"
//         "mov ax, 0x10;"
//         "mov ds, ax;"
//         "mov es, ax;"
//         "mov fs, ax;"
//         "mov gs, ax;"
//         "pop eax;"
//         "1: ret;");
// }

// __attribute__((naked)) static void restore_segment_regs_if_needed(void)
// {
//     __asm__(
//         "cmpd [esp + 8], 0x1b;"
//         "jne restore_segment_regs_if_needed__return;"
//         "push eax;"
//         "mov ax, 0x23;"
//         "mov ds, ax;"
//         "mov es, ax;"
//         "mov fs, ax;"
//         "mov gs, ax;"
//         "pop eax;"
//         "restore_segment_regs_if_needed__return:"
//         "ret;");
// }

// // IRQ 0
// __attribute__((naked)) static void interrupt_handler_0x20(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[0])
//         irq_handlers[0]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 1
// __attribute__((naked)) static void interrupt_handler_0x21(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[1])
//         irq_handlers[1]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 2
// __attribute__((naked)) static void interrupt_handler_0x22(void)
// {
//     write_serial("Spurious IRQ 2.");
// }

// // IRQ 3
// __attribute__((naked)) static void interrupt_handler_0x23(void)
// {
//     write_serial("Spurious IRQ 3.");
// }

// // IRQ 4
// __attribute__((naked)) static void interrupt_handler_0x24(void)
// {
//     write_serial("Spurious IRQ 0x04.");
// }

// // IRQ 5
// __attribute__((naked)) static void interrupt_handler_0x25(void)
// {
//     write_serial("Spurious IRQ 5.");
// }

// // IRQ 6
// __attribute__((naked)) static void interrupt_handler_0x26(void)
// {
//     write_serial("Spurious IRQ 6.");
// }

// // IRQ 7
// __attribute__((naked)) static void interrupt_handler_0x27(void)
// {
//     write_serial("Spurious IRQ 7.");
// }

// // IRQ 8
// __attribute__((naked)) static void interrupt_handler_0x28(void)
// {
//     write_serial("Spurious IRQ 8.");
// }

// // IRQ 9
// __attribute__((naked)) static void interrupt_handler_0x29(void)
// {
//     write_serial("Spurious IRQ 9.");
// }

// // IRQ 10
// __attribute__((naked)) static void interrupt_handler_0x2a(void)
// {
//     write_serial("Spurious IRQ 10.");
// }

// // IRQ 11
// __attribute__((naked)) static void interrupt_handler_0x2b(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[11])
//         irq_handlers[11]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 12
// __attribute__((naked)) static void interrupt_handler_0x2c(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[12])
//         irq_handlers[12]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 13
// __attribute__((naked)) static void interrupt_handler_0x2d(void)
// {
//     write_serial("Spurious IRQ 13.");
// }

// // IRQ 14
// __attribute__((naked)) static void interrupt_handler_0x2e(void)
// {
//     write_serial("Spurious IRQ 14.");
// }

// // IRQ 15
// __attribute__((naked)) static void interrupt_handler_0x2f(void)
// {
//     write_serial("Spurious IRQ 15.");
// }

// // INT 0x80
// // Replace pushad/popad with individual pushes/pops if necessary.
// __attribute__((naked)) static void interrupt_handler_0x80(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("sub esp, 4");
//     __asm__("push eax\n push ecx\n push edx\n push ebx\n push esp\n push ebp\n push esi\n push edi");
//     sys_dispatch();
//     __asm__("mov [esp + 32], eax");
//     __asm__("pop edi\n pop esi\n pop ebp\n pop esp\n pop ebx\n pop edx\n pop ecx\n pop eax");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// void SET_IRQ_HANDLER(uint8_t IRQ, void(*handler))
// {
//     irq_handlers[IRQ] = handler;
// }

// // PIC

// /*
// arguments:
//     offset1 - vector offset for master PIC
//         vectors on the master become offset1..offset1+7
//     offset2 - same for slave PIC: offset2..offset2+7
// */
// void PIC_REMAP(int offset1, int offset2)
// {
//     uint8_t a1, a2;

//     a1 = inPort_B(PIC1_DATA); // save masks
//     a2 = inPort_B(PIC2_DATA);

//     outPort_B(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
//     io_Wait();
//     outPort_B(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
//     io_Wait();
//     outPort_B(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
//     io_Wait();
//     outPort_B(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
//     io_Wait();
//     outPort_B(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
//     io_Wait();
//     outPort_B(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
//     io_Wait();

//     outPort_B(PIC1_DATA, ICW4_8086); // ICW4: have the PICs use 8086 mode (and not 8080 mode)
//     io_Wait();
//     outPort_B(PIC2_DATA, ICW4_8086);
//     io_Wait();

//     outPort_B(PIC1_DATA, a1); // restore saved masks.
//     outPort_B(PIC2_DATA, a2);
// }

// void PIC_DISABLE()
// {
//     outPort_B(PIC1_DATA, 0xff);
//     outPort_B(PIC2_DATA, 0xff);
// }

// void IRQ_SET_MASK(uint8_t IRQline)
// {
//     uint16_t port;
//     uint8_t value;

//     if (IRQline < 8)
//     {
//         port = PIC1_DATA;
//     }
//     else
//     {
//         port = PIC2_DATA;
//         IRQline -= 8;
//     }
//     value = inPort_B(port) | (1 << IRQline);
//     outPort_B(port, value);
// }

// void IRQ_CLEAR_MASK(uint8_t IRQline)
// {
//     uint16_t port;
//     uint8_t value;

//     if (IRQline < 8)
//     {
//         port = PIC1_DATA;
//     }
//     else
//     {
//         port = PIC2_DATA;
//         IRQline -= 8;
//     }
//     value = inPort_B(port) & ~(1 << IRQline);
//     outPort_B(port, value);
// }

// /* Helper func */
// static uint16_t __PIC_GET_IRQ_REQ(int ocw3)
// {
//     /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
//      * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
//     outPort_B(PIC1_COMMAND, ocw3);
//     outPort_B(PIC2_COMMAND, ocw3);
//     return (inPort_B(PIC2_COMMAND) << 8) | inPort_B(PIC1_COMMAND);
// }

// /* Returns the combined value of the cascaded PICs irq request register */
// uint16_t PIC_GET_IRR()
// {
//     return __PIC_GET_IRQ_REQ(PIC_READ_IRR);
// }

// /* Returns the combined value of the cascaded PICs in-service register */
// uint16_t PIC_GET_ISR()
// {
//     return __PIC_GET_IRQ_REQ(PIC_READ_ISR);
// }

// void INIT_IDT()
// {
//     IDT_ptr.base_ptr = (uintptr_t)&IDT[0];
//     IDT_ptr.limit = (uint16_t)sizeof(IDT_Entry) * IDT_SIZE - 1;

//     IDT_SET_DESCRIPTOR(0x00, exception_handler_0x00, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x01, exception_handler_0x01, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x02, exception_handler_0x02, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x03, exception_handler_0x03, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x04, exception_handler_0x04, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x05, exception_handler_0x05, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x06, exception_handler_0x06, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x07, exception_handler_0x07, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x08, exception_handler_0x08, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x09, exception_handler_0x09, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0a, exception_handler_0x0a, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0b, exception_handler_0x0b, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0c, exception_handler_0x0c, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0d, exception_handler_0x0d, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0e, exception_handler_0x0e, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x10, exception_handler_0x10, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x11, exception_handler_0x11, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x12, exception_handler_0x12, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x13, exception_handler_0x13, RING_0_INTERRUPT_GATE);

//     IDT_SET_DESCRIPTOR(0x20, interrupt_handler_0x20, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x21, interrupt_handler_0x21, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x22, interrupt_handler_0x22, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x23, interrupt_handler_0x23, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x24, interrupt_handler_0x24, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x25, interrupt_handler_0x25, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x26, interrupt_handler_0x26, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x27, interrupt_handler_0x27, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x28, interrupt_handler_0x28, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x29, interrupt_handler_0x29, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2a, interrupt_handler_0x2a, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2b, interrupt_handler_0x2b, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2c, interrupt_handler_0x2c, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2d, interrupt_handler_0x2d, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2e, interrupt_handler_0x2e, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2f, interrupt_handler_0x2f, RING_0_INTERRUPT_GATE);

//     IDT_SET_DESCRIPTOR(0x80, interrupt_handler_0x80, RING_3_TRAP_GATE);

//     __asm__ volatile("lidt %0" : : "m"(IDT_ptr)); // load the new IDT

//     __asm__ volatile("sti"); // set the interrupt flag {master pic is 32-47, slave pic is 48-63}
//     write_serial("Remapped PIC...\n");
// }

// #include "include/idt.h"

// __attribute__((aligned(0x10))) static IDT_Entry IDT[IDT_SIZE];

// static IDT_Locator IDT_ptr;

// static void (*irq_handlers[16])();

// __attribute__((noreturn)) void EXCEPTION_HANDLER(char *msg)
// {
//     __asm__ volatile("cli");
//     write_serial("EXCEPTION: ");
//     write_serial(msg);
//     write_serial("\n");
//     __asm__ volatile("hlt");
// }

// __attribute__((noreturn)) void EXCEPTION_HANDLER_WITH_ERR_CODE(char *msg, uint32_t err_code)
// {
//     __asm__ volatile("cli");
//     write_serial("EXCEPTION: ");
//     write_serial(msg);
//     write_serial(" Error code: ");
//     write_serial_hex(err_code);
//     write_serial("\n");
//     __asm__ volatile("hlt");
// }

// void IDT_SET_DESCRIPTOR(uint8_t vector, void *isr, uint8_t flags)
// {

//     IDT[vector].base_low = (uint32_t)isr & 0xFFFF;
//     IDT[vector].selector = GDT_CODE_SEGMENT;
//     IDT[vector].zero = 0;
//     IDT[vector].flags = flags;
//     IDT[vector].base_high = (uint32_t)isr >> 16;
// }

// static bool vectors[IDT_SIZE] = {false};

// extern void *isr_stub_table[];

// __attribute__((naked)) static void exception_handler_0x00(void)
// {
//     exception(0x00);
// }

// __attribute__((naked)) static void exception_handler_0x01(void)
// {
//     exception(0x01);
// }

// __attribute__((naked)) static void exception_handler_0x02(void)
// {
//     exception(0x02);
// }

// __attribute__((naked)) static void exception_handler_0x03(void)
// {
//     exception(0x03);
// }

// __attribute__((naked)) static void exception_handler_0x04(void)
// {
//     exception(0x04);
// }

// __attribute__((naked)) static void exception_handler_0x05(void)
// {
//     exception(0x05);
// }

// __attribute__((naked)) static void exception_handler_0x06(void)
// {
//     exception(0x06);
// }

// __attribute__((naked)) static void exception_handler_0x07(void)
// {
//     exception(0x07);
// }

// __attribute__((naked)) static void exception_handler_0x08(void)
// {
//     __asm__(
//         "push 0x08\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x09(void)
// {
//     exception(0x09);
// }

// __attribute__((naked)) static void exception_handler_0x0a(void)
// {
//     __asm__(
//         "push 0x0a\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0b(void)
// {
//     __asm__(
//         "push 0x0b\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0c(void)
// {
//     __asm__(
//         "push 0x0c\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0d(void)
// {
//     __asm__(
//         "push 0x0d\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x0e(void)
// {
//     __asm__(
//         "push 0x0e\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x10(void)
// {
//     exception(0x10);
// }

// __attribute__((naked)) static void exception_handler_0x11(void)
// {
//     __asm__(
//         "push 0x11\n"
//         "call exception_with_code");
// }

// __attribute__((naked)) static void exception_handler_0x12(void)
// {
//     exception(0x12);
// }

// __attribute__((naked)) static void exception_handler_0x13(void)
// {
//     exception(0x13);
// }

// void INIT_IDT()
// {
//     IDT_ptr.base_ptr = (uintptr_t)&IDT[0];
//     IDT_ptr.limit = (uint16_t)sizeof(IDT_Entry) * IDT_SIZE - 1;

//     IDT_SET_DESCRIPTOR(0x00, exception_handler_0x00, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x01, exception_handler_0x01, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x02, exception_handler_0x02, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x03, exception_handler_0x03, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x04, exception_handler_0x04, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x05, exception_handler_0x05, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x06, exception_handler_0x06, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x07, exception_handler_0x07, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x08, exception_handler_0x08, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x09, exception_handler_0x09, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0a, exception_handler_0x0a, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0b, exception_handler_0x0b, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0c, exception_handler_0x0c, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0d, exception_handler_0x0d, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x0e, exception_handler_0x0e, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x10, exception_handler_0x10, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x11, exception_handler_0x11, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x12, exception_handler_0x12, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x13, exception_handler_0x13, RING_0_INTERRUPT_GATE);

//     IDT_SET_DESCRIPTOR(0x20, interrupt_handler_0x20, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x21, interrupt_handler_0x21, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x22, interrupt_handler_0x22, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x23, interrupt_handler_0x23, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x24, interrupt_handler_0x24, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x25, interrupt_handler_0x25, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x26, interrupt_handler_0x26, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x27, interrupt_handler_0x27, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x28, interrupt_handler_0x28, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x29, interrupt_handler_0x29, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2a, interrupt_handler_0x2a, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2b, interrupt_handler_0x2b, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2c, interrupt_handler_0x2c, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2d, interrupt_handler_0x2d, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2e, interrupt_handler_0x2e, RING_0_INTERRUPT_GATE);
//     IDT_SET_DESCRIPTOR(0x2f, interrupt_handler_0x2f, RING_0_INTERRUPT_GATE);

//     IDT_SET_DESCRIPTOR(0x80, interrupt_handler_0x80, RING_3_TRAP_GATE);

//     __asm__ volatile("lidt %0" : : "m"(IDT_ptr)); // load the new IDT

//     __asm__ volatile("sti"); // set the interrupt flag {master pic is 32-47, slave pic is 48-63}
//     write_serial("Remapped PIC...\n");
// }

// // PIC

// /*
// arguments:
//     offset1 - vector offset for master PIC
//         vectors on the master become offset1..offset1+7
//     offset2 - same for slave PIC: offset2..offset2+7
// */
// void PIC_REMAP(int offset1, int offset2)
// {
//     uint8_t a1, a2;

//     a1 = inPort_B(PIC1_DATA); // save masks
//     a2 = inPort_B(PIC2_DATA);

//     outPort_B(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
//     io_Wait();
//     outPort_B(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
//     io_Wait();
//     outPort_B(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
//     io_Wait();
//     outPort_B(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
//     io_Wait();
//     outPort_B(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
//     io_Wait();
//     outPort_B(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
//     io_Wait();

//     outPort_B(PIC1_DATA, ICW4_8086); // ICW4: have the PICs use 8086 mode (and not 8080 mode)
//     io_Wait();
//     outPort_B(PIC2_DATA, ICW4_8086);
//     io_Wait();

//     outPort_B(PIC1_DATA, a1); // restore saved masks.
//     outPort_B(PIC2_DATA, a2);
// }

// void PIC_DISABLE()
// {
//     outPort_B(PIC1_DATA, 0xff);
//     outPort_B(PIC2_DATA, 0xff);
// }

// void IRQ_SET_MASK(uint8_t IRQline)
// {
//     uint16_t port;
//     uint8_t value;

//     if (IRQline < 8)
//     {
//         port = PIC1_DATA;
//     }
//     else
//     {
//         port = PIC2_DATA;
//         IRQline -= 8;
//     }
//     value = inPort_B(port) | (1 << IRQline);
//     outPort_B(port, value);
// }

// void IRQ_CLEAR_MASK(uint8_t IRQline)
// {
//     uint16_t port;
//     uint8_t value;

//     if (IRQline < 8)
//     {
//         port = PIC1_DATA;
//     }
//     else
//     {
//         port = PIC2_DATA;
//         IRQline -= 8;
//     }
//     value = inPort_B(port) & ~(1 << IRQline);
//     outPort_B(port, value);
// }

// /* Helper func */
// static uint16_t __PIC_GET_IRQ_REQ(int ocw3)
// {
//     /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
//      * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
//     outPort_B(PIC1_COMMAND, ocw3);
//     outPort_B(PIC2_COMMAND, ocw3);
//     return (inPort_B(PIC2_COMMAND) << 8) | inPort_B(PIC1_COMMAND);
// }

// /* Returns the combined value of the cascaded PICs irq request register */
// uint16_t PIC_GET_IRR()
// {
//     return __PIC_GET_IRQ_REQ(PIC_READ_IRR);
// }

// /* Returns the combined value of the cascaded PICs in-service register */
// uint16_t PIC_GET_ISR()
// {
//     return __PIC_GET_IRQ_REQ(PIC_READ_ISR);
// }

// __attribute__((naked)) static void restore_segment_regs_if_needed(void)
// {
//     __asm__(
//         "cmpd [esp + 8], 0x1b;"
//         "jne restore_segment_regs_if_needed__return;"
//         "push eax;"
//         "mov ax, 0x23;"
//         "mov ds, ax;"
//         "mov es, ax;"
//         "mov fs, ax;"
//         "mov gs, ax;"
//         "pop eax;"
//         "restore_segment_regs_if_needed__return:"
//         "ret;");
// }

// // IRQ 0
// __attribute__((naked)) static void interrupt_handler_0x20(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[0])
//         irq_handlers[0]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 1
// __attribute__((naked)) static void interrupt_handler_0x21(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[1])
//         irq_handlers[1]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 2
// __attribute__((naked)) static void interrupt_handler_0x22(void)
// {
//     write_serial("Spurious IRQ 2.");
// }

// // IRQ 3
// __attribute__((naked)) static void interrupt_handler_0x23(void)
// {
//     write_serial("Spurious IRQ 3.");
// }

// // IRQ 4
// __attribute__((naked)) static void interrupt_handler_0x24(void)
// {
//     write_serial("Spurious IRQ 0x04.");
// }

// // IRQ 5
// __attribute__((naked)) static void interrupt_handler_0x25(void)
// {
//     write_serial("Spurious IRQ 5.");
// }

// // IRQ 6
// __attribute__((naked)) static void interrupt_handler_0x26(void)
// {
//     write_serial("Spurious IRQ 6.");
// }

// // IRQ 7
// __attribute__((naked)) static void interrupt_handler_0x27(void)
// {
//     write_serial("Spurious IRQ 7.");
// }

// // IRQ 8
// __attribute__((naked)) static void interrupt_handler_0x28(void)
// {
//     write_serial("Spurious IRQ 8.");
// }

// // IRQ 9
// __attribute__((naked)) static void interrupt_handler_0x29(void)
// {
//     write_serial("Spurious IRQ 9.");
// }

// // IRQ 10
// __attribute__((naked)) static void interrupt_handler_0x2a(void)
// {
//     write_serial("Spurious IRQ 10.");
// }

// // IRQ 11
// __attribute__((naked)) static void interrupt_handler_0x2b(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[11])
//         irq_handlers[11]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 12
// __attribute__((naked)) static void interrupt_handler_0x2c(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("pushad");
//     if (irq_handlers[12])
//         irq_handlers[12]();
//     __asm__("popad");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// // IRQ 13
// __attribute__((naked)) static void interrupt_handler_0x2d(void)
// {
//     write_serial("Spurious IRQ 13.");
// }

// // IRQ 14
// __attribute__((naked)) static void interrupt_handler_0x2e(void)
// {
//     write_serial("Spurious IRQ 14.");
// }

// // IRQ 15
// __attribute__((naked)) static void interrupt_handler_0x2f(void)
// {
//     write_serial("Spurious IRQ 15.");
// }

// // INT 0x80
// __attribute__((naked)) static void interrupt_handler_0x80(void)
// {
//     set_segment_regs_if_needed();
//     __asm__("sub esp, 4");
//     __asm__("pushad");
//     sys_dispatch();
//     __asm__("mov [esp + 32], eax");
//     __asm__("popad");
//     __asm__("pop eax");
//     restore_segment_regs_if_needed();
//     __asm__("iret");
// }

// void SET_IRQ_HANDLER(uint8_t IRQ, void(*handler))
// {
//     irq_handlers[IRQ] = handler;
// }

#include "include/idt.h"

__attribute__((aligned(0x10))) static IDT_Entry IDT[IDT_SIZE];

static IDT_Locator IDT_ptr;

__attribute__((noreturn)) void EXCEPTION_HANDLER(char *msg)
{
    __asm__ volatile("cli");
    write_serial("EXCEPTION: ");
    write_serial(msg);
    write_serial("\n");
    __asm__ volatile("hlt");
}
void IDT_SET_DESCRIPTOR(uint8_t vector, void *isr, uint8_t flags)
{

    IDT[vector].base_low = (uint32_t)isr & 0xFFFF;
    IDT[vector].selector = GDT_CODE_SEGMENT;
    IDT[vector].zero = 0;
    IDT[vector].flags = flags;
    IDT[vector].base_high = (uint32_t)isr >> 16;
}

static bool vectors[IDT_SIZE] = {false};

extern void *isr_stub_table[];

void INIT_IDT()
{
    IDT_ptr.base_ptr = (uintptr_t)&IDT[0];
    IDT_ptr.limit = (uint16_t)sizeof(IDT_Entry) * IDT_SIZE - 1;

    for (uint8_t vector = 0; vector < 32; vector++)
    {
        IDT_SET_DESCRIPTOR(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    write_serial("IDT: Initialized ISR stubs...\n");

    __asm__ volatile("lidt %0" : : "m"(IDT_ptr)); // load the new IDT
    __asm__ volatile("sti");                      // set the interrupt flag
    PIC_REMAP(PIC1, PIC2);

    write_serial("Remapped PIC...\n");
}

// PIC

/*
arguments:
    offset1 - vector offset for master PIC
        vectors on the master become offset1..offset1+7
    offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_REMAP(int offset1, int offset2)
{
    uint8_t a1, a2;

    a1 = inPort_B(PIC1_DATA); // save masks
    a2 = inPort_B(PIC2_DATA);

    outPort_B(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
    io_Wait();
    outPort_B(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_Wait();
    outPort_B(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
    io_Wait();
    outPort_B(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
    io_Wait();
    outPort_B(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_Wait();
    outPort_B(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_Wait();

    outPort_B(PIC1_DATA, ICW4_8086); // ICW4: have the PICs use 8086 mode (and not 8080 mode)
    io_Wait();
    outPort_B(PIC2_DATA, ICW4_8086);
    io_Wait();

    outPort_B(PIC1_DATA, a1); // restore saved masks.
    outPort_B(PIC2_DATA, a2);
}

void PIC_DISABLE()
{
    outPort_B(PIC1_DATA, 0xff);
    outPort_B(PIC2_DATA, 0xff);
}

void IRQ_SET_MASK(uint8_t IRQline)
{
    uint16_t port;
    uint8_t value;

    if (IRQline < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inPort_B(port) | (1 << IRQline);
    outPort_B(port, value);
}

void IRQ_CLEAR_MASK(uint8_t IRQline)
{
    uint16_t port;
    uint8_t value;

    if (IRQline < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inPort_B(port) & ~(1 << IRQline);
    outPort_B(port, value);
}

/* Helper func */
static uint16_t __PIC_GET_IRQ_REQ(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outPort_B(PIC1_COMMAND, ocw3);
    outPort_B(PIC2_COMMAND, ocw3);
    return (inPort_B(PIC2_COMMAND) << 8) | inPort_B(PIC1_COMMAND);
}

/* Returns the combined value of the cascaded PICs irq request register */
uint16_t PIC_GET_IRR()
{
    return __PIC_GET_IRQ_REQ(PIC_READ_IRR);
}

/* Returns the combined value of the cascaded PICs in-service register */
uint16_t PIC_GET_ISR()
{
    return __PIC_GET_IRQ_REQ(PIC_READ_ISR);
}
