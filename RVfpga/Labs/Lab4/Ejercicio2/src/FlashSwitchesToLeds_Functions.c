// memory-mapped I/O addresses
#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

void IOsetup();
unsigned int getSwitchesVal();
void writeValtoLEDs(unsigned int val);
void delay(int num);

int main ( void )
{
  unsigned int switches_val;

  IOsetup();
  while (1) { 
    switches_val = getSwitchesVal();
    writeValtoLEDs(switches_val);
    delay(20000000);  // Delay para que se vea el valor en los leds
    writeValtoLEDs(0x0000); // Apagamos los leds
    delay(20000000);  // Delay para mantenerlos apagados un tiempo
  }

  return(0);
}

void IOsetup()
{
  int En_Value=0xFFFF;
  WRITE_GPIO(GPIO_INOUT, En_Value);
}

unsigned int getSwitchesVal()
{ 
  unsigned int val;

  val = READ_GPIO(GPIO_SWs);   // read value on switches        
  val = val >> 16;  // shift into lower 16 bits

  return val;
}

void writeValtoLEDs(unsigned int val)
{
  WRITE_GPIO(GPIO_LEDs, val);  // display val on LEDs
}

void delay(int num){
    // Esta funcion es simplemente un bucle del tamaño del delay que se le pase
    // como parametro. Como el for no hace nada, para que el compilador no se lo
    // salte, hay que añadir la instrucción volatile al int.
    for(int volatile i = 1; i < num; i++){}
}
