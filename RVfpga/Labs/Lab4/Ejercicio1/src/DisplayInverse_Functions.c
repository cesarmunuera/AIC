// memory-mapped I/O addresses
#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

void IOsetup();
unsigned int getSwitchesInvert();
void writeValtoLEDs(unsigned int val);

int main ( void )
{
  unsigned int switches_val;

  IOsetup();
  while (1) { 
    switches_val = getSwitchesInvert();
    writeValtoLEDs(switches_val);
  }

  return(0);
}

void IOsetup()
{
  int En_Value=0xFFFF;
  WRITE_GPIO(GPIO_INOUT, En_Value);
}

unsigned int getSwitchesInvert()
{ 
  unsigned int val;

  val = READ_GPIO(GPIO_SWs);   // read value on switche        
  val = val >> 16;  // shift into lower 16 bits

  return ~val;  // Este es la unica modificacion al codigo, un inversor
  // De esta forma, retornará el valor contrario al que se ha introducido
}

void writeValtoLEDs(unsigned int val)
{
  WRITE_GPIO(GPIO_LEDs, val);  // display val on LEDs
}
