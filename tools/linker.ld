/* ########################################################################## */
/*                                                                            */
/*                  PELO AMOR DE DEUS NÃO MEXE NESSE ARQUIVO.                 */
/*           NEM EU SEI DIREITO O QUE SIGNIFICA ESSAS COISAS AQUI,            */
/*              SÓ SEI QUE ELAS SÃO AS CONFIGURAÇÕES DO LINKER.               */
/*                                                                            */
/*        SE VOCÊ NÃO SABE O QUE É LINKER, SÓ SAIBA QUE É IMPORTANTE          */
/*               E SE ESTRAGAR ELE O PROJETO TODO NÃO FUNCIONA.               */
/*                                                                            */
/*     Se você se garante muito pode mexer a vontade, mas não recomendo.      */
/*                                                                            */
/* ########################################################################## */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00200000, LENGTH = 0x0007FFFF
    FLASH_CCA (RX) : ORIGIN = 0x0027FFBF, LENGTH = 96
    SRAM_NON_RETENTION (RWX) : ORIGIN =  0x20000000, LENGTH = 0x00004000
    SRAM_RETENTION (RWX) : ORIGIN = 0x20004000, LENGTH = 0x00004000
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH= 0
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
    } > FLASH_CCA   
}