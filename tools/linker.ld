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
        _stext = .;
        KEEP(*(.vectors*))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    /* Section in which initialized data is placed */
    .data : {
        _sdata = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM_RETENTION AT> FLASH
    
    /* Section in which uninitialized data is placed */
    .bss : {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM_RETENTION

    /* Program heap is placed entirely on the non retention SRAM */
    _heap = ORIGIN(SRAM_NON_RETENTION);
    _eheap = ORIGIN(SRAM_NON_RETENTION) + LENGTH(SRAM_NON_RETENTION);
 
    .flashcca : { 
        KEEP(*(.flashcca))
    } > FLASH_CCA   
}