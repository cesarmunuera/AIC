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
  int En_Value = 0xFFFF, i, j, k, vActual, hex_integer;

  WRITE_GPIO(GPIO_INOUT, En_Value);

  WRITE_GPIO(GPIO_LEDs, 0xFFFF); // display switch value on LEDs

  for (i = 0; i < 15; i++) {

    for (j = 1; j < 16; j++){
      vActual = j * 2;
      sprintf(hex_integer, "0x%04X", vActual);

      WRITE_GPIO(GPIO_LEDs, hex_integer);
    }
    
    for (k = 1; k < 16; k++){
      vActual = j / 2;
      sprintf(hex_integer, "0x%04X", vActual);

      WRITE_GPIO(GPIO_LEDs, hex_integer);
    }

  }

  return (0);
}
