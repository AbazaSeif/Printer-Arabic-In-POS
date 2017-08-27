MEMORY
{
  irom (rx) : ORIGIN = 0x00000000, LENGTH = 128K
  itcm (rx) : ORIGIN = 0x00600000, LENGTH = 4K
  dtcm (rw) : ORIGIN = 0x00700000, LENGTH = 4K
  iram (rwx) : ORIGIN = 0x00900000, LENGTH = 384K
  iram_novect (rwx) : ORIGIN = 0x00901000, LENGTH = 380K
  iram1 (rwx) : ORIGIN = 0x00900000, LENGTH = 64K
  iram2 (rwx) : ORIGIN = 0x00910000, LENGTH = 320K
  nvsram (rwx) : ORIGIN = 0x00A00000, LENGTH = 64K
  iram_a (rwx) : ORIGIN = 0xFFFF0000, LENGTH = 64K
  iram_avect (rwx) : ORIGIN = 0xFFFF0000, LENGTH = 4K
  nand (rw) : ORIGIN = 0x10000000, LENGTH = 512M
  sram (rwx) : ORIGIN = 0x30000000, LENGTH = 64M
  nor (rw) : ORIGIN = 0x40000000, LENGTH = 32M
  sdram0 (rwx) : ORIGIN = 0x70000000, LENGTH = 512M
  sdram1 (rwx) : ORIGIN = 0x90000000, LENGTH = 512M
}
EXTERN(__reset __reset_core1)
PROVIDE(__reset = __reset_core1);
