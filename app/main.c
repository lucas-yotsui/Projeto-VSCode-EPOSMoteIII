// ########################################################## //
//                                                            //
//       Seu loop principal vai aqui, se quiser criar         //
//     bibliotecas pra organizar seu código em arquivos       //
//    separados, fique a vontade desde que os arquivos de     //
//    código fonte estejam na pasta source e os arquivos      // 
//          de cabeçalho estejam na pasta include.            //
//                                                            //
//     Logo, a estrutura recomendada seria parecida com:      //
//                 meu_projeto                                //     
//                   |                                        //
//                   |-app                                    //
//                   |  |- main.c                             //
//                   |  |- startup_gcc.c                      //
//                   |                                        //
//                   |-include                                //
//                   |  |- meu_codigo.h                       //
//                   |                                        //
//                   |-source                                 //
//                   |  |- meu_codigo.c                       //
//                   |                                        //
//                                                            //
// ########################################################## //

#include "meu_codigo.h"

int main(void)  {
    configureMote();
    
    while (true) {
        blinkLED();
    }
}