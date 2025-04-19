# RadonOS static memory mappings

PDE = Page Directory Entry (0 index)
PTE = Page Table Entry (0 index)

## Application

### Stack

PDE 0

### Application program/static data

PDE 1-254

### Heap

PDE 255-766

## Kernel

### BIOS/Bootloader/Hardware reserved

PDE 767, PTE 0-255
Mapped to 0x00000000-0x00100000

### Kernel program/static data

PDE 767, PTE 256-1023
Mapped to 0x00100000-0x00400000

### Framebuffer

PDE 1022

### Page directory

PDE 1023
