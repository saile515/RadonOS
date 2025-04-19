.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set VMT, 1<<2
.set FLAGS, ALIGN | MEMINFO | VMT
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align   4
.long    MAGIC
.long    FLAGS
.long    CHECKSUM
.skip    20
.long    0
.long    0
.long    0
.long    0

.section .bss
.align   16

stack_bottom:
 .skip 16384

stack_top:

.align   4096
page_directory:
  .skip 4096

page_table0:
  .skip 4096

.section .text
.global  _start
.type    _start, @function

_start:
  // Initialize stack
  movl $stack_top, %esp

  // Initalize FPU
  fninit

  // Push multiboot header
  push %eax
  push %ebx

  // Identity map first 4MB
  movl $page_table0, %eax
  orl $0x3, %eax
  movl %eax, page_directory

  movl $0x0, %eax
  movl $0x0, %ebx
  .fill_identity_map:
    movl %ebx, %ecx
    orl $0x3, %ecx
    movl %ecx, page_table0(,%eax,4)
    addl $0x1000, %ebx
    incl %eax
    cmpl $0x1000, %eax
    jne .fill_identity_map

  // Map page directory to last page table
  movl $page_directory, %eax
  orl $0x3, %eax
  movl %eax, page_directory + 0xFFC

  // Initalize paging
  movl $page_directory, %eax
  movl %eax, %cr3
  movl %cr0, %eax
  orl $0x80000001, %eax
  movl %eax, %cr0

  call kernel_main

  cli

1:
  hlt
  jmp 1b

.size _start, . - _start
