/* * ---------------------------------------------------------------------- * */
/* |                                                                        | */
/* |                PELO AMOR DE DEUS NÃO MEXE NESSE ARQUIVO,               | */
/* |                  ESSAS SÃO AS CONFIGURAÇÕES DO LINKER.                 | */
/* |                                                                        | */
/* |      SE VOCÊ NÃO SABE O QUE É LINKER, SÓ SAIBA QUE É IMPORTANTE        | */
/* |             E SE ESTRAGAR ELE O PROJETO TODO NÃO FUNCIONA.             | */
/* |                                                                        | */
/* |   Se você se garante muito pode mexer a vontade, mas não recomendo.    | */
/* |                                                                        | */
/* * ---------------------------------------------------------------------- * */

/* EPOSMoteIII is based on a CC2538SF53 from Texas Instruments if you want to 
check some documentation and modify this file */

MEMORY {
    FLASH(rx) : ORIGIN = 0x00200000, LENGTH = 0x0007FFD4
    FLASH_CCA(rx) : ORIGIN = 0x0027FFD4, LENGTH = 0x0000002C
    SRAM_NON_RETENTION(rwx) : ORIGIN =  0x20000000, LENGTH = 0x00004000
    SRAM_RETENTION(rwx) : ORIGIN = 0x20004000, LENGTH = 0x00004000
    STACK(rwx) : ORIGIN = 0x20007E00, LENGTH = 0x00000200
}

ENTRY(reset_handler)

SECTIONS {
    /* Section in which code is placed */
    .text : {
        _stext = .;         /* Linker symbol marking the start of the .text section for reference in code */
        KEEP(*(.vectors*))  /* Interrupts vector */
        *(.text*)           /* Code */
        *(.rodata*)         /* Read-onl data (const variables) */
        _etext = .;         /* Linker symbol marking the end of the .text section for reference in code */
    } > FLASH

    /* Section in which initialized data is placed */
    .data : {
        _sdata = .;         /* Linker symbol marking the start of the .data section for reference in code */
        *(vtable)           /* Runtime interrupts vector */
        *(.data*)           /* Initialized variables */
        _edata = .;         /* Linker symbol marking the end of the .data section for reference in code */
    } > SRAM_RETENTION AT> FLASH
    
    /* Section in which uninitialized data is placed */
    .bss : {
        _sbss = .;          /* Linker symbol marking the start of the .bss section for reference in code */
        *(.bss*)            /* Uninitialized variables or initialized to 0 */
        *(COMMON)           /* Common symbols (not really sure what they are ¯\_(ツ)_/¯) */
        _ebss = .;          /* Linker symbol marking the end of the .bss section for reference in code */
    } > SRAM_RETENTION

    /* Program heap is placed entirely on the non retention SRAM */
    /*! Dynamic memory allocation in embedded is almost always a bad idea! Even though this is called !*/
    /*!  heap it should not be used for that, rather it's intended to be used when some extra memory  !*/
    /*!  is needed. Please take note that this memory region does not retain its data after entering  !*/
    /*!                                          sleep mode.                                          !*/
    _heap = ORIGIN(SRAM_NON_RETENTION);
    _eheap = ORIGIN(SRAM_NON_RETENTION) + LENGTH(SRAM_NON_RETENTION);
    
    /* Customer Configuration Area + Page Lock Bits (more info about both on the CC2538 User Guide) */
    .flashcca : { 
        KEEP(*(.flashcca))  /* CCA + Lock Page bits */
    } > FLASH_CCA   
}