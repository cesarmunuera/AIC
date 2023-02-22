// memory-mapped I/O addresses
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

repeat:
  lw   t1, 0(t0)      # Lee lo que hay en la dirección de t0, y lo mete a t1
  srli t1, t1, 16     # shift val to the right by 16 bits
  sw   t1, 4(t0)      # Desplazamos t0 hasta GPIO_LEDs, y escribimos alli el contenido de t1
  j    repeat         # repeat loop