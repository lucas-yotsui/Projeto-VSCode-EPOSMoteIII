/* ########################################################################## */
/*                                                                            */
/*                  PELO AMOR DE DEUS NÃO MEXE NESSE ARQUIVO,                 */
/*                    ESSAS SÃO AS CONFIGURAÇÕES DO LINKER.                   */
/*                                                                            */
/*        SE VOCÊ NÃO SABE O QUE É LINKER, SÓ SAIBA QUE É IMPORTANTE          */
/*               E SE ESTRAGAR ELE O PROJETO TODO NÃO FUNCIONA.               */
/*                                                                            */
/*     Se você se garante muito pode mexer a vontade, mas não recomendo.      */
/*                                                                            */
/* ########################################################################## */

/* EPOSMoteIII is based on a CC2538SF53 from Texxas Instruments if you want to 
check some documentation and modify this file */

MEMORY {
    FLASH(rx) : ORIGIN = 0x00200000, LENGTH = 512K - 32
    FLASH_CCA(rx) : ORIGIN = 0x0027FFE0, LENGTH = 32
    SRAM_RETENTION(rwx) : ORIGIN = 0x20000000, LENGTH = 16K
    SRAM_NON_RETENTION(rwx) : ORIGIN =  0x20004000, LENGTH = 16K
}

ENTRY(resetHandler)

SECTIONS {
    .text :
    {
        _stext = .;
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : 
    {
        _sdata = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM_NON_RETENTION AT> FLASH
    
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM_NON_RETENTION
 
    .flashcca :
    { 
        *(.flashcca)
    } > FLASH_CCA   
}