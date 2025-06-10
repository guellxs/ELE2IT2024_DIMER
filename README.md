# Biblioteca ELE2IT_DIMER

Essa biblioteca tem como objetivo controlar o brilho de uma lâmpada através de ZCD e TRIAC.

A detecção por zero acontece através de um sistema de interrupção, que chama a função responsável por iniciar o timer.

O timer é definido através de um cálculo, que transforma o delay de acionamento do triac em porcentagem.

Os circuito utilizado para desenvolvimento da biblioteca está anexado na pasta rescursos.

- Antes de definir o brilho, deve-se iniciar a biblioteca e escolher/iniciar os pinos utilizados;
- O brilho da lâmpada deve ser definido de um valor de 0 (mínimo) a 100 (máximo).
