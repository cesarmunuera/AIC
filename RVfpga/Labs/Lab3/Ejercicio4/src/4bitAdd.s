# GPIO_SWs   = 0x80001400
# GPIO_LEDs  = 0x80001404
# GPIO_INOUT = 0x80001408

.globl main

# Leemos del switch
main:
  li t0, 0x80001400   # En t0 guardamos la direccion GPIO_SWs
  li t1, 0xFFFF       # En t1 guardamos FFFF
                      # upper half = switches (inputs)  (=0)
                      # lower half = outputs (LEDs)     (=1)
  sw t1, 8(t0)        # Desplazamos 8 en hex a t0 (llega a GPIO_INOUT), y le metemos t1


# Guardamos en t2 el valor del switch
lw t2, 0(t0)
li t4, 0xF0000000

# Guardamos en t3 los 4 bits mas altos
and t3, t2, t4

# Desplazamos los 4 bits a las ultimas posiciones
srli t3, t3, 28

# Ahora vamos a por los bit mas bajos. Desplazamos 16 hacia la derecha
srli t2, t2, 16

# Multiplicamos por una mascara para dejarla limpia
li t4, 0x0000000F
and t2, t2, t4

# Hacemos la suma
add t2, t2, t3

# Almacenamos el resultado en las posiciones mas bajas de los LEDs
sw t2, 4(t0)

j main