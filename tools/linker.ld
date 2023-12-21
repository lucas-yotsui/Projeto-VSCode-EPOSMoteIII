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

/* CC2538SF53 */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00200000, LENGTH = 0x0007FFFF
    FLASH_CCA (RX) : ORIGIN = 0x0027F800, LENGTH = 0x000007FF
    SRAM_NON_RETENTION (RWX) : ORIGIN =  0x20000000, LENGTH = 0x00004000
    SRAM_RETENTION (RWX) : ORIGIN = 0x20004000, LENGTH = 0x00004000
}

ENTRY(__cca)

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM_NON_RETENTION
    
    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM_NON_RETENTION
 
    .flashcca :
    { 
        *(.flashcca)
    } > FLASH_CCA   
}