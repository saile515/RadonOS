# RadonOS static memory mappings

PDE = Page Directory Entry
PTE = Page Table Entry

## Kernel

PDE 1
Kernel starts at PTE 512. Earlier entries are identity mapped and reserved for BIOS/Hardware.

## Page directory

PDE 1024

# Framebuffer

PDE 1023
