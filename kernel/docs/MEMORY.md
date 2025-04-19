# RadonOS static memory mappings

PDE = Page Directory Entry
PTE = Page Table Entry

## Kernel

PDE 768
Kernel starts at PTE 256. Earlier entries are reserved for BIOS/Hardware.
The entire PDE is mapped 1:1 to 0x00000000-0x00400000

# Framebuffer

PDE 1023

## Page directory

PDE 1024
