# Projeto EPOSMoteIII no Visual Studio Code
[![Documentação EPOSMoteIII](https://img.shields.io/badge/Documentação_EPOSMoteIII-blue?logo)](https://epos.lisha.ufsc.br/EPOSMote+III)
![GitHub issues](https://img.shields.io/github/issues/lucas-yotsui/Projeto-VSCode-EPOSMoteIII?logo=github)
![github-stars](https://img.shields.io/github/stars/lucas-yotsui/Projeto-VSCode-EPOSMoteIII?logo=github)
[![github-release-version](https://img.shields.io/github/v/release/lucas-yotsui/Projeto-VSCode-EPOSMoteIII?logo=github)](https://github.com/lucas-yotsui/Projeto-VSCode-EPOSMoteIII/releases)
![GitHub](https://img.shields.io/github/license/lucas-yotsui/Projeto-VSCode-EPOSMoteIII)

## Introdução

Esse repositório é um template para criação de projetos baseados na placa EposMoteIII desenvolvida no Laboratório de Integração Software e Hardware filiado à Universidade Federal de Santa Catarina. 

A intenção deste projeto é possibilitar o desenvolvimento de aplicações voltadas à placa EPOSMoteIII desenvolvida pelo LISHA sem o uso do projeto EPOS. A intenção por trás da remoção dessa camada é de permitir o uso deste hardware no processo de aprendizado da programação de sistemas embarcados, uma vez que neste processo é necessário criar um bom entendimento do funcionamento interno do hardware, sem tais abstrações.

Para tal, esse projeto utiliza as bibliotecas disponibilizadas pela própria fabricante para o microcontrolador no qual se baseia a placa, um CC2538 da Texas Instruments.

O projeto foi desenvolvido para uso com o editor Visual Studio Code com a extensão CMakeTools, de forma que quando aberto neste editor ele o configura da forma necessária utilizando o gerador recomendado para o CMake e com as configurações do Intellisense que otimizam sua utilização.

O uso deste editor não é obrigatório, porém o projeto foi concebido para ser utilizado nele, logo, para uso fora dele fazem-se necessárias algumas adaptações para utilizá-lo.

## Sobre o EPOSMoteIII

Como dito anteriormente, o EPOSMoteIII é baseado em um microcontrolador CC2538 da Texas Intruments, um poderoso chip baseado em uma arquitetura 32-bit Arm Cortex-M3 com uma memória flash de 512 kB, 32kB de RAM, suporte nativo a comunicação ZigBee, 6LoWPAN e IEEE 802.15.4 e clock de até 32 MHz. 

![EPOSMoteIII](https://epos.lisha.ufsc.br/display113) 

A placa foi desenvolvida pelo LISHA de forma a ter o menor tamanho possível para ser utilizada principalmente em projetos de IoT. Alguns kits de expansão também foram desnevolvidos para ela, como o [Smart Plug Module](https://epos.lisha.ufsc.br/Smart+plug+board) ou a [Hydrologic Station Board](https://epos.lisha.ufsc.br/Hydrologic+Station+board).

Para mais informações a respeito do EPOSMoteIII ou dos kits de expansão, confira a documentação oficial no site do projeto no botão no topo desta página.

## Pré-Requisitos

Para o uso deste projeto, não é necessária a instalação prévia de nenhum componente, uma vez que o instalador baixa todas as dependências.

## Instalação

Para instalar este projeto, basta utilizar o instalador incluso neste repositório, baixando este instalador e executando-o. Encerrado este processo, esse instalador exibirá um menu com orientações sobre o uso do projeto.

## Uso

Caso esteja utilizando o Visual Studio Code com a extensão CMakeTools, ao abrir seu projeto haverá uma barra na parte inferior da janela parecida com a seguinte:

![Barra de Utilidades CMake](https://imgur.com/ysdXhI9.png)

Nesta barra, há algumas opções importantes para o uso do projeto. A primeira delas é o _**botão de seleção de variante de build**_, responsável por determinar o nível de otimização do processo de compilação e inserir informações de debug no executável gerado.

![Botão Otimização](https://imgur.com/qNVVxRr.png)

Em geral, uma vez que não é possível depurar o EPOSMoteIII sem uma interface do tipo JTAG, não é necessário utilizar a variante _**Debug**_. Logo, deve-se usar na maioria dos casos a variante _**Release**_.

O botão seguinte é o de _**seleção de kit de desenvolvimento**_, responsável por selecionar o kit de desenvolvimento utilizado no processo de compilação. 

kit
![Botão selecionar kit](https://imgur.com/V9cH11l.png)

Ao clicar neste botão, o seguinte menu aparece para selecionar o kit de desenvolvimento desejado. Uma vez que o EPOSMoteIII é baseado em uma arquitetura ARM, deve-se utilizar um kit _**arm-none-eabi**_.

![Menu seleção kit](https://imgur.com/3cVdoqA.png)

O botão seguinte é o de _**build**_, responsável por iniciar o processo de compilação do projeto.

![Botão build](https://imgur.com/r3pnJmK.png)

O último botão relevante a este projeto é o de _**seleção de alvo para build**_.

![Botão de seleção de alvo](https://imgur.com/7qqNFPZ.png)

Ao clicar neste botão, o seguinte menu é exibido:

![Menu seleção alvo](https://imgur.com/Z7QqVSF.png)

As duas opções mais importantes nesse menu são _**projeto**_ e _**flash**_. A primeira é o alvo utilizado apenas para compilar seu programa, ou seja, esta opção apenas cria o executável. A segunda por sua vez faz o upload do executável para o EPOSMoteIII através do programa utilitário baixado pelo instalador deste projeto.

Após selecionado o alvo, deve-se pressionar o botão de build para realizar o processo selecionado, seja ele o de compilação ou o de flash.

### Testando o projeto

Junto com este projeto, é incluso um programa simples que faz o LED on-board do EPOSMoteIII piscar que pode ser usado para testar as funções de upload do executável e analisar a estrutura do projeto que será explicada no tópico seguinte.

Para fazer upload deste exemplo para sua placa, siga os seguintes passos (que também se aplicam para seus projetos futuros baseados nesse template):

1. Crie uma cópia da pasta _Projeto-VSCode-EPOSMoteIII_.

2. Renomeie esta nova pasta para o nome que deseja dar ao seu projeto.

3. Abra essa nova pasta no Visual Studio Code.

4. Selecione o kit de desenvolvimento ARM (_**arm-none-eabi**_).

5. Selecione a variante de build _**Release**_.

6. Selecione o alvo _**flash**_.

7. Clique em _**build**_ (Com a placa ainda desconectada do computador).

8. Siga as instruções na janela do programa de flash.

## Estrutura do projeto

Este projeto é dividido em alguns componentes, que serão explicados individualmente a seguir:

### .vscode

Este diretório contém um único arquivo responsável por selecionar o gerador desejado para o CMake e configurar o projeto para salvar as alterações feitas sempre que um comando build for lançado, de forma a prevenir a perda de alterações feitas no projeto por esquecer de salvar manualmente.

Caso deseje alterar estes comportamentos ou adicionar alguma configuração extra ao editor, sinta-se a vontade para customizar este arquivo livremente. Para guiá-lo neste processo, há uma extensa documentação da Microsoft sobre as configurações possíveis e seus respectivos comandos na internet. Divirta-se :grin:

### app

Este é o diretório no qual vivem dois dos arquivos mais importantes em seu projeto: _main.c_ e _startup_gcc.c_.

O primeiro é onde fica sua função main, ponto de entrada de qualquer aplicação. Já o segundo é onde são configuradas as interrupções e timers utilizados no seu projeto, além de outras configurações da memória às quais não cabe explicação aqui.

### build

Este é o diretório criado pelo CMake onde será armazenado o executável do seu programa.

Este diretório é criado e alterado pelo CMake e sua única preocupação com ele deve ser excluí-lo em algumas situações para remediar alguns erros que pode encontrar.

**Casos em que se deve excluir a pasta _build_**

1. Erros que não fazem sentido estão sendo encontrados no seu projeto (includes corretos, erros já corrigidos, etc).

2. Foram feitas alterações nas configurações do CMake e elas não parecem estar surtindo efeito.

3. Foi escolhido um outro compilador ou gerador do CMake.

### cmake

Neste diretório vive o arquivo _**arm-none-eabi-toolchain.cmake** (nome grande eu sei, mas juro que ele é bem explicativo pra quem sabe o que significa)_, responsável por configurar o script CMakeLists.txt para cross-compiling para arquitetura ARM.

Este é um dos diretórios que não precisam ser alterados na maioria dos projetos e devem ser feitos somente por usuários com um entendimento médio ou avançado de programação, uma vez que as configurações feitas nele são essenciais para o projeto.

### include

Este diretório é onde devem ser colocados os headers que forem criados em seu projeto. O arquivo _**CMakeLists.txt**_ incluso está configurado para definir este diretório como uma das fontes de include do projeto.

Dessa forma, todos os arquivos _.h_ diretamente neste diretório podem ser incluídos em outras partes do projeto sem especificar o caminho completo para eles. Ou seja, no exemplo incluso,
```c
#include <meu_codigo.h>
```
é completamente funcional em qualquer parte do projeto, uma vez que este arquivo vive na raíz do diretório include.

### source

Este diretório é onde devem ser colocados os arquivos de código fonte que forem criados em seu projeto. O arquivo _**CMakeLists.txt**_ incluso está configurado para compilar todos os arquivos _.c_ ou _.cpp_ presentes aqui.

Dessa forma, os arquivos _.h_ criados na pasta include podem ter as definições de suas funções nos arquivos _.c_ nesta pasta. No exemplo incluso, o arquivo _**meu_codigo.c**_ define as funções declaradas em _**meu_codigo.h**_

### tools

Este diretório é onde ficam os dois arquivos utilitários usados pelo projeto. O primeiro é o _**linker.ld**_, responsável por mapear as regiões de memória para o processo de linking da compilação. O segundo é o _**bootloader.c**_, um arquivo com funções utilizadas para o processo de bootloader (necessário para que se possa fazer flash de um novo programa sem o uso de uma interface como uma JTAG).

Não é necessário alterar nada neste arquivo, tudo já está configurado para funcionar com o EPOSMoteIII. Entretanto, aqueles que possuem mais experiência com programação voltada a sistemas embarcados, devem sentir-se a vontade para alterar estes arquivos da forma que julgar melhor. A propósito, caso o faça, fique a vontade para sugerir a alteração neste repositório, criando uma nova _**pull request**_.

### CMakeLists.txt

Este arquivo vive na raíz do projeto e é responsável por configurar o CMake para compilar e fazer o flash deste projeto corretamente.

Este arquivo está configurado propriamente e poucas alterações cabem aos usuários, a principal delas é a seguinte linha:
```CMake
# Compiler warnings
set(COMPILER_WARNINGS 
    -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 
    -mfloat-abi=hard -ffunction-sections -fdata-sections
    -Wall -Wextra -pedantic -MD -fno-exceptions -fno-rtti
)
```
Este trecho é responsável por definir os warnings usados na compilação e podem ser ajustados às preferências do usuário (à exceção dos 6 primeiros, específicos da plataforma alvo).