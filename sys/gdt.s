; .global GDT_FLUSH_AND_LOAD

; GDT_FLUSH_AND_LOAD:
;     movl 4(%esp), %eax
;     lgdt (%eax)

;     movw $0x10, %ax  # The first entry is the NULL selector, then we define a 32-bit code segment (starting at offset 0x08 of the GDT) and a 32-bit data segment (starting at offset 0x10 of the GDT)
;     movw %ax, %ds
;     movw %ax, %es
;     movw %ax, %fs
;     movw %ax, %gs
;     movw %ax, %ss
    
;     # Jump to the code segment
;     ljmp $0x08, $.flush

; .flush: 
;     ret
