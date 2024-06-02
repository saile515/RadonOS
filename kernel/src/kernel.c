#include "framebuffer.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>
#include <stdint.h>

void kernel_main(multiboot_info_t *multiboot_info, uint32_t magic) {
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    return;
  }

  framebuffer_init((uint32_t *)multiboot_info->framebuffer_addr,
                   multiboot_info->framebuffer_width,
                   multiboot_info->framebuffer_height);

  terminal_init(framebuffer_width / 8, framebuffer_height / 16);
  terminal_write("Welcome to RadonOS!\n");
  terminal_write(
      "Testing really long line "
      "............................................................."
      "............................................................."
      ".............................................................\n");

  int i = 1;
  int frame = 0;

  while (true) {
    if (i % 100000000 == 0) {
      terminal_write("Testing scrolling ");
      terminal_write(frame % 2 == 0 ? "1\n" : "2\n");
      terminal_render();

      i = 0;
      frame++;
    }

    i++;
  }
}
