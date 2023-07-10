// ########################################################## //
//                                                            //
//         Este é um exemplo de biblioteca criada para        //
//               organizar melhor o código.                   //
//                                                            //
//     No formato sugerido, todos os includes necessários     //
//    e os cabeçalhos de funções são feitos aqui, ao passo    //
//    que no arquivo .c ficam as definições dessas funções.   //
//                                                            //
//      Caso seus includes ainda apareçam destacados como     // 
//     errados ou inexistentes, tente compilar o código uma   //
//    vez (comando build). As configurações do Intellisense   //
//    (o que gera essas marcações de erro) são geradas pelo   // 
//    CMake e podem não funcionar corretamente enquanto não   //
//                for feita essa compilação.                  //
//                                                            //
// ########################################################## //

#ifndef _MEU_CODIGO_H_
#define _MEU_CODIGO_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "source/gpio.h"
#include <source/sys_ctrl.h>

void configureMote(void);
void blinkLED(void);

#endif