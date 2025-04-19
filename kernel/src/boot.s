.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set VMT, 1<<2
.set FLAGS, ALIGN | MEMINFO | VMT
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot.data, "aw"
.align   4
.long    MAGIC
.long    FLAGS
.long    CHECKSUM
.skip    20
.long    0
.long    0
.long    0
.long    0

.section .bootstrap_stack, "aw", @nobits
stack_bottom:
 .skip 16384

stack_top:

.section .bss, "aw", @nobits
page_directory:
  .skip 4096

page_table0:
  .skip 4096

multiboot_info_pointer:
  .skip 4

multiboot_magic:
  .skip 4

.section .multiboot.text, "a"
.global _start
.type _start, @function
_start:  
  // Store multiboot header
  movl %ebx, multiboot_info_pointer - 0xC0000000
  movl %eax, multiboot_magic - 0xC0000000

  // Initalize FPU
  fninit

  // Identity map first 4MB, and map to 0xC0000000
  movl $(page_table0 - 0xC0000000), %eax
  orl $0x3, %eax
  movl %eax, page_directory - 0xC0000000
  movl %eax, page_directory - 0xC0000000 + 0xC00

  movl $0x0, %eax
  movl $0x0, %ebx
  .fill_kernel_page_table:
    movl %ebx, %ecx
    orl $0x3, %ecx
    movl %ecx, (page_table0 - 0xC0000000)(,%eax,4)
    addl $0x1000, %ebx
    incl %eax
    cmpl $0x400, %eax
    jne .fill_kernel_page_table

  // Map page directory to last page table
  movl $(page_directory - 0xC0000000), %eax
  orl $0x3, %eax
  movl %eax, page_directory - 0xC0000000 + 0xFFC

  // Initalize paging
  movl $(page_directory - 0xC0000000), %eax
  movl %eax, %cr3
  movl %cr0, %eax
  orl $0x80000001, %eax
  movl %eax, %cr0

  leal 1f, %eax
  jmp *%eax

.section .text
1:
  // Remove identity mapping of first page table
  movl $0x0, page_directory

  // Initialize stack
  movl $stack_top, %esp
  movl $stack_top, %ebp

  addl $0xC0000000, multiboot_info_pointer
  push multiboot_magic
  push multiboot_info_pointer

  call kernel_main

  cli
2:
  hlt
  jmp 2b
