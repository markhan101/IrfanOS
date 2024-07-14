global GDT_FLUSH_AND_LOAD

GDT_FLUSH_AND_LOAD:
    
    MOV EAX, [ESP+4]
    LGDT [EAX]

    MOV EAX, 0X10 # The first entry is the NULL selector then we define a 32-bit code segment (starting at offset 0x08 of the GDT) and a 32-bit data segment (starting at offset 0x10 of the GDT)

    MOV DS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    MOV SS, AX
    
    # Jump on to the code segment
    JMP 0X08:
        .FLUSH

    .FLUSH: 
        RET

