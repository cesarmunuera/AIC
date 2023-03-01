# GPIO_SWs   = 0x80001400
# GPIO_LEDs  = 0x80001404
# GPIO_INOUT = 0x80001408

.globl main


main:
  li t0, 0x80001400   # En t0 guardamos GPIO_SWs
  li t1, 0xFFFF       # En t1 guardamos FFFF
                      # upper half = switches (inputs)  (=0)
                      # lower half = outputs (LEDs)     (=1)
  sw t1, 8(t0)        # Desplazamos 8 en hex a t0 (llega a GPIO_INOUT), y le metemos t1
  
  li t1, 0x0          # Registro con los LEDs que vamos a desplazar
  li s1, 0x00000010   # Numero de LEDs 
  li s2, 0x300000     # Delay


# Sirve para resetear valores cuando se termina completamente la primera ejecucion
reset:
  li t5, 0x0
  li t1, 0x0

# Comenzamos comprobando si hemos terminado, para luego ir aumentando los bits a desplazar
inicio:
  beq t5, s1, reset   # Comprobamos si el contador t5 ya ha llegado a 16
  slli t1, t1, 1      # Desplazamos un bit a la izquierda
  addi t1, t1, 1      # Sumamos 1 bit (un led por la derecha)
  addi t5, t5, 1      # Aumentamos el contador, hemos hecho una pasada
  addi t4, t5, 0      # Nos guardamos el contador en t4 tambien
  
subida:
  sw t1, 4(t0)        # Imprimimos los leds
  li t3, 0x00000000   # Reseteamos el contador del delay

time1:                # DELAY                          
  addi t3, t3, 1
  bne  t3, s2, time1

# Una vez que se ha mostrado y mantenido un tiempo el led, comprobamos si hemos acabado de subir
subida2:
  beq t4, s1, bajadaI # Si el contador que empieza = n LEDs encendidos es 16, vamos a bajada
  slli t1, t1, 1      # Desplazamos a la izquierda
  addi t4, t4, 1      # Aumentamos el contador. Debemos desplazar 16-nLEDs encendidas
  j subida            # Si no ha terminado de subir, vuelve a iterar


# Reseteamos el valor de t4 con el del contador t5
bajadaI:
  addi t4, t5, 0

bajada:
  sw t1, 4(t0)        # Imprimimos los leds
  li t3, 0x00000000   # Reseteamos el contador del dela

time2:                # Delay                              
  addi t3, t3, 1
  bne  t3, s2, time2

# Una vez que se ha mostrado y mantenido un tiempo el led, comprobamos si hemos acabado de bajar
bajada2:
  beq t4, s1, inicio  # Si el contador que empieza = n LEDs encendidos es 16, volvemos a inicio
  srli t1, t1, 1      # Desplazamos a la derecha
  addi t4, t4, 1      # Aumentamos el contador. Debemos desplazar 16-nLEDs encendidas
  j bajada            # si no ha terminado de bajar, vuelve a iterar