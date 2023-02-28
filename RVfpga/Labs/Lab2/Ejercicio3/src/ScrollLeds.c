#include <stdio.h>
#include <stdlib.h>
// memory-mapped I/O addresses
#define GPIO_SWs 0x80001400
#define GPIO_LEDs 0x80001404
#define GPIO_INOUT 0x80001408
#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value)             \
  {                                        \
    (*(volatile unsigned *)dir) = (value); \
  }
int main(void)
{
  int En_Value = 0xFFFF;
  WRITE_GPIO(GPIO_INOUT, En_Value);
  int valor;
  int num1, num2 = 0;
  int max;
  while (1)
  {
    for (int i = 1; i <= 16; i++)
    {
      num1 = (num1 << 1) | 1;
      max = 16 / i;
      for (int j = 1; j <= max; j++)
      {
        if (j == 1)
        {
          valor = num1 * 2;
        }
        else
        {
          valor = valor * 2;
        }
        WRITE_GPIO(GPIO_LEDs, valor);
      }

      for (int k = 1; k <= max; k++)
      {
        valor = valor / 2;
        WRITE_GPIO(GPIO_LEDs, valor);
      }
    }
  }
  return (0);
}