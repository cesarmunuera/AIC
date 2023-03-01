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
  
  li t1, 0x0

  li t2, 0x00000002
  li s1, 0x00000010   # Numero de LEDs 
  li s2, 0x300000     # Delay


# Aumentamos el numero a desplazar
reset:
  li t5, 0x0
  li t1, 0x0
inicio:
  beq t5, s1, reset
  slli t1, t1, 1
  addi t1, t1, 1
  addi t5, t5, 1    # Aumentamos el contador, hemos hecho una pasada
  addi t4, t5, 0
  


# Desplazamos a la izquierda
subida:
  sw t1, 4(t0)

  li t3, 0x00000000   # Numero de LEDs
time1:                               
  addi t3, t3, 1
  bne  t3, s2, time1

subida2:
  beq t4, s1, bajadaI
  slli t1, t1, 1
  addi t4, t4, 1
  j subida


# Desplazamos a la derecha
bajadaI:
  addi t4, t5, 0
bajada:
  sw t1, 4(t0) 

  li t3, 0x00000000   # Numero de LEDs
time2:                               
  addi t3, t3, 1
  bne  t3, s2, time2

bajada2:
  beq t4, s1, inicio
  srli t1, t1, 1
  addi t4, t4, 1
  j bajada