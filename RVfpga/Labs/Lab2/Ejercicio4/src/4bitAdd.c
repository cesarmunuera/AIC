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

        op1 = switches_value >> 12;             //Las 4 primeras posiciones, guardadas en las 4 posiciones mas bajas de op1.
        op2 = switches_value & 0x000F;          //Las últimas 4 posiciones, guardadas en las 4 posiciones mas bajas de op2.

        resultado = op1 + op2;                  //Esto es como sumar n + 0x000n, guardandose en las posiciones mas bajas 

        WRITE_GPIO(GPIO_LEDs, resultado);       //Se imprimen en las posiciones mas bajas

        /*El acarreo no puedo hacerlo, no se como reacciona la placa ante esa suma, no puedo testear un input. Pero podria
        * multiplicarse por una mascara como 0x00F0. Si la salida es distinta de 0, es que tiene acarreo, y se se puede
        * setear un 0.
        */
    }
    return (0);
}