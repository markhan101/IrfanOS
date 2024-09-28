; Define macros for ISR stubs
%macro isr_err_stub 1
isr_stub_%+%1:
    call EXCEPTION_HANDLER
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    push word %1
    push dword isr_msg_%+%1
    call EXCEPTION_HANDLER
    iret
%endmacro

extern EXCEPTION_HANDLER  ; Declare the external exception handler

section .data
isr_msg_0 db "Divide by Zero", 0
isr_msg_1 db "Debug", 0
isr_msg_2 db "Non Maskable Interrupt", 0
isr_msg_3 db "Breakpoint", 0
isr_msg_4 db "Into Detected Overflow", 0
isr_msg_5 db "Out of Bounds", 0
isr_msg_6 db "Invalid Opcode", 0
isr_msg_7 db "No Coprocessor", 0
isr_msg_8 db "Double Fault", 0
isr_msg_9 db "Coprocessor Segment Overrun", 0
isr_msg_10 db "Bad TSS", 0
isr_msg_11 db "Segment Not Present", 0
isr_msg_12 db "Stack Fault", 0
isr_msg_13 db "General Protection Fault", 0
isr_msg_14 db "Page Fault", 0
isr_msg_15 db "Unknown Interrupt", 0
isr_msg_16 db "Coprocessor Fault", 0
isr_msg_17 db "Alignment Check", 0
isr_msg_18 db "Machine Check", 0
isr_msg_19 db "Reserved", 0
isr_msg_20 db "Reserved", 0
isr_msg_21 db "Reserved", 0
isr_msg_22 db "Reserved", 0
isr_msg_23 db "Reserved", 0
isr_msg_24 db "Reserved", 0
isr_msg_25 db "Reserved", 0
isr_msg_26 db "Reserved", 0
isr_msg_27 db "Reserved", 0
isr_msg_28 db "Reserved", 0
isr_msg_29 db "Reserved", 0
isr_msg_30 db "Reserved", 0
isr_msg_31 db "Reserved", 0

; Define exception handlers
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

; Define the stub table
global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
    dd isr_stub_%+i    
%assign i i + 1 
%endrep
