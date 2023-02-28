#include <stdio.h>
#include <stdlib.h>
// memory-mapped I/O addresses
#define GPIO_SWs 0x80001400
#define GPIO_LEDs 0x80001404
#define GPIO_INOUT 0x80001408
#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value)                 \
    {                                          \
        (*(volatile unsigned *)dir) = (value); \
    }
int main(void)
{
    int En_Value = 0xFFFF, switches_value;
    WRITE_GPIO(GPIO_INOUT, En_Value);
    int op1, op2, resultado = 0x0000;
    while (1)
    {
        switches_value = READ_GPIO(GPIO_SWs);
        op1 = 0x34560000 & 0xF0000000; // Aplicamos una
        //mascara de forma que solo quean en op1 los 4 bits mas
            significativos.op2 = 0x34530000 & 0x000F0000; // Aplicamos una
        //mascara de forma que solo quean en op1 los 4 bits menos
            significativos.op1 = op1 >> 12; // Movemos los bits mas significativos a la
        //posicion de los menos significativos para sumarlos
            resultado = op1 + op2; // Esto es como
        //sumar n + 0x000n, guardandose en las posiciones mas bajas
                              resultado = resultado >> 16; // Los bits que enciendes los
       // leds se encuentran en las posiciones más bajas de la memoria asi
            //que debemos moverlos
                WRITE_GPIO(GPIO_LEDs, resultado); // Se imprimen en
        //las posiciones mas bajas
        /*El acarreo no puedo hacerlo, no se como reacciona la
       placa ante esa suma, no puedo testear un input. Pero podria
        * multiplicarse por una mascara como 0x00F0. Si la salida
       es distinta de 0, es que tiene acarreo, y se se puede
        * setear un 0.
        */
    }
    return (0);
}