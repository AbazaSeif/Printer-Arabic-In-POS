OUTPUT_FORMAT ("elf32-littlearm")
ENTRY(__reset)
SEARCH_DIR(.)
INCLUDE memories.inc
INCLUDE layout.inc
EXTERN(__start_asm _start)
INCLUDE arm-names.inc
EXTERN(__start_c main __stack __heap_end)
__heap_size = 24M;
__stack_size = 4M;
__section_cpu_context_size = 64;
SECTIONS
{
  .bootstrap :
  {
    *(.rvect)
    *(.reset)
  } > sdram0
  .text.init : ALIGN(32)
  {
    __INIT_SECTION__ = . ;
    _init = . ;
    _start = DEFINED(__start_asm) ? __start_asm : _start;
    __handler_undefined__ = DEFINED(__handler_undefined) ? __handler_undefined : __handler_undefined_;
    __handler_swi__ = DEFINED(__handler_swi) ? __handler_swi : __handler_swi_;
    __handler_prefetch__ = DEFINED(__handler_prefetch) ? __handler_prefetch : __handler_prefetch_;
    __handler_abort__ = DEFINED(__handler_abort) ? __handler_abort : __handler_abort_;
    __handler_irq__ = DEFINED(__handler_irq) ? __handler_irq : __handler_irq_;
    __handler_fiq__ = DEFINED(__handler_fiq) ? __handler_fiq : __handler_fiq_;
    _handler_undefined_ = DEFINED(handler_undefined) ? handler_undefined : handler_undefined_;
    _handler_swi_ = DEFINED(handler_swi) ? handler_swi : handler_swi_;
    _handler_prefetch_ = DEFINED(handler_prefetch) ? handler_prefetch : handler_prefetch_;
    _handler_abort_ = DEFINED(handler_abort) ? handler_abort : handler_abort_;
    _handler_irq_ = DEFINED(handler_irq) ? handler_irq : handler_irq_;
    _handler_fiq_ = DEFINED(handler_fiq) ? handler_firq : handler_fiq_;
 *(.text.init0)
 *(.text.init)
    *(.handlers)
    __FINI_SECTION__ = . ;
    _fini = . ;
  } > sdram0
  .text : ALIGN(32)
  {
   __section_start_text = .;
    *(.reftable)
    *(.text .text.* .gnu.linkonce.t.*)
    *(.plt)
    *(.gnu.warning)
    *(.glue_7t) *(.glue_7) *(.vfp11_veneer)
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    *(.gcc_except_table)
    . = ALIGN(32);
    __section_end_text = .;
  } >sdram0
  __section_size_text = __section_end_text - __section_start_text;
  __section_wsize_text = __section_size_text / 4;
  __section_load_text = LOADADDR(.text);
  .itcm : ALIGN (32)
  {
    __region_start_itcm = .;
    __section_start_itcm = .;
    *(.itcm)
    . = ALIGN(32);
    __section_end_itcm = .;
  } >itcm AT>sdram0
  __section_size_itcm = __section_end_itcm - __section_start_itcm;
  __section_wsize_itcm = __section_size_itcm / 4;
  __section_load_itcm = LOADADDR(.itcm);
  .eh_frame_hdr : ALIGN (4)
  {
    KEEP (*(.eh_frame_hdr))
  } >sdram0
  .eh_frame : ALIGN (4)
  {
    KEEP (*(.eh_frame))
  } >sdram0
  PROVIDE_HIDDEN (__exidx_start = .);
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >sdram0
  PROVIDE_HIDDEN (__exidx_end = .);
  .rodata : ALIGN (4)
  {
    *(.rodata .rodata.* .gnu.linkonce.r.*)
  } >sdram0
  .dtcm : ALIGN (32)
  {
    __region_start_dtcm = .;
    __section_start_data_dtcm = .;
    *(.dtcm)
    . = ALIGN(32);
    __section_end_data_dtcm = .;
  } >dtcm AT>sdram0
  __section_size_data_dtcm = __section_end_data_dtcm - __section_start_data_dtcm;
  __section_wsize_data_dtcm = __section_size_data_dtcm / 4;
  __section_load_data_dtcm = LOADADDR (.dtcm);
  .data :
  {
   __section_start_data = .;
    KEEP(*(.jcr))
    *(.got.plt) *(.got)
    *(.shdata)
    *(.data .data.* .gnu.linkonce.d.*)
    *(.igot.plt* .init_array.*)
    . = ALIGN(32);
    __section_end_data = .;
  } >sdram0
  __section_size_data = __section_end_data - __section_start_data;
  __section_wsize_data = __section_size_data / 4;
  __section_load_data = LOADADDR(.data);
  .bss (NOLOAD) : ALIGN(32)
  {
    __section_start_bss = .;
    *(.lib.ram)
    *(.shbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    __section_end_bss = .;
  } >sdram0
  .cpu_context (NOLOAD) : ALIGN (4)
  {
    __section_cpu_context_start = __section_end_bss;
    . = . + __section_cpu_context_size;
  __section_cpu_context_end = .;
  } > sdram0
  .stack (NOLOAD) : ALIGN(32)
  {
   __section_start_stack = .;
   . = . + __stack_size;
   __stack = .;
   __section_end_stack = .;
  } > sdram0
  __stack_va = 0xFFF00000 + __stack_size;
  .heap (NOLOAD) : ALIGN(32)
  {
    __section_start_heap = .;
    . = . + __heap_size;
    __section_end_heap = .;
     __region_end_ram = .;
  } > sdram0
  __section_start_heap_va = 0xFFF02000;
  __section_end_heap_va = __section_start_heap_va + __heap_size;
  .dtcm.bss (NOLOAD) :
  {
    __section_start_bss_dtcm = .;
    *(.dtcm.b .bss.dtcm)
    . = ALIGN(4);
    __section_end_bss_dtcm = .;
  } >dtcm
  .stab 0 (NOLOAD) : { *(.stab) }
  .stabstr 0 (NOLOAD) : { *(.stabstr) }
  .debug 0 : { *(.debug) }
  .line 0 : { *(.line) }
  .debug_srcinfo 0 : { *(.debug_srcinfo) }
  .debug_sfnames 0 : { *(.debug_sfnames) }
  .debug_aranges 0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_line 0 : { *(.debug_line) }
  .debug_frame 0 : { *(.debug_frame) }
  .debug_str 0 : { *(.debug_str) }
  .debug_loc 0 : { *(.debug_loc) }
  .debug_macinfo 0 : { *(.debug_macinfo) }
  .debug_ranges 0 : { *(.debug_ranges) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
  /DISCARD/ : {
    *(.note.GNU-stack)
    *(.comment)
    *(.vect)
    *(.ttbl2)
    *(.ttb)
   }
}
SECTIONS
{
 .mon.NVSRAM1 0xFFF10100 (NOLOAD) :
 {
  __section_start_NVSRAM1 = .;
  *(.NVSRAM1)
  . = __section_start_NVSRAM1 + 0x400;
  *(.NVSRAM1.PINPAD)
  . = ALIGN(4);
 }
}
SECTIONS
{
 .usb.INTRAM 0x00958000 (NOLOAD) :
 {
  *(.INTRAM .INTRAM.*)
 }
}
SECTIONS
{
  .iram2 (NOLOAD) : ALIGN (8)
  {
    *(.iram2)
  } > iram2
 .macb_base 0xffe70000 (NOLOAD) :
 {
     *(.macb_regs)
  . = ALIGN(32);
 }
}
