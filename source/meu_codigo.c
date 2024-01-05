// ########################################################## //
//                                                            //
//      Aqui estão as definições das funções declaradas       //
//          no arquivo meu_codigo.h na pasta include          //
//                                                            //
//      Repare que antes de cada função e da variável há      //
//        um comentário iniciado por /**. Esse tipo de        //
//       comentário segue o estilo Javadoc e é utilizado      //
//       para documentar o código. No VS Code, quando é       //
//     empregado este padrão, essa documentação é exibida     //
//     ao passar o mouse por cima da função ou variável e     //
//       enquanto escreve o código como um menu de ajuda.     //
//          Tente passar o mouse por cima da variável         //
//      colorController, tanto em sua declaração, quanto na   //
//         sua chamada na função blinkLED para ver essa       //
//    funcionalidade. Tente também passar o mouse por cima    //
//   das chamadas dessas funções nos arquivos meu_codigo.h    //
//                        e main.c                            //
//                                                            //
//        Caso deseje explorar mais essa funcionalidade,      //
//     esse formato de documentação é usada principalmente    //
//      com Doxygen, para o qual é fácil encontrar guias      //
//      e tutoriais na internet, incluindo a documentação     //
//      oficial do Doxygen. A sintaxe é muito simples com     //
//   algumas tags como @brief, @details, @note, @param, etc.  //
//                                                            //
// ########################################################## //

#include "meu_codigo.h"

/**
 * @brief Define o clock do Tiva em 40 MHz e ativa o portal
 * F da GPIO, definindo o pino 3 como saída.
*/
void configureMote(void) {
    // Define o clock do sistema como 32 MHz.
    SysCtrlClockSet(true, true, SYS_CTRL_SYSDIV_32MHZ);

    // Define o clock dos portais de I/O como 32 MHz.
    SysCtrlIOClockSet(SYS_CTRL_SYSDIV_32MHZ);

    // Define o pino 3 do portal C como saída.
    GPIOPinTypeGPIOOutput(GPIO_C_BASE, GPIO_PIN_3);
}

/**
 * @brief Pisca o LED
*/
void blinkLED(void) {
    // Acende o LED 
    GPIOPinWrite(GPIO_C_BASE, GPIO_PIN_3, GPIO_PIN_3);
    // Adiciona um pequeno delay.
    SysCtrlDelay(20000000);

    // Apaga o LED para criar o efeito de piscar.
    GPIOPinWrite(GPIO_C_BASE, GPIO_PIN_3, 0x00);
    // Adiciona um pequeno delay.
    SysCtrlDelay(20000000);
}