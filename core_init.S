
#include "s3c2440_regs.h"
#include "configs.h"


@Exception vector table
.text
.global _start
_start:
@0x00: Reset
	b reset

@0x04: Undefined instructions
	ldr pc, exception_undef_instruction

@0x08: SWI
	ldr pc, exception_swi

@0x0c: Prefetch Abort
	ldr pc, exception_prefetch_abort

@0x10: Data Abort
	ldr pc, exception_data_abort

@0x14: Not Used
	ldr pc, exception_not_used

@0x18: IRO
	ldr pc, exception_irq

@0x1c: FIQ
	ldr pc, exception_fiq

exception_undef_instruction	: .word handle_undef_instruction
exception_swi			: .word handle_swi
exception_prefetch_abort	: .word handle_prefetch_abort
exception_data_abort		: .word handle_data_abort
exception_not_used		: .word handle_not_used
exception_irq			: .word handle_irq
exception_fiq			: .word handle_fiq

handle_undef_instruction:
	nop

handle_swi:
	nop

handle_prefetch_abort:
	nop

handle_data_abort:
	nop

handle_not_used:
	nop

handle_irq:
	nop

handle_fiq:
	nop

@reset entrypoint
reset:
	@bl set_svc
	bl disable_watchdog
	bl disable_interrupt
	bl disable_mmu
	bl init_sys_clk
	bl init_mem_ctl
	bl init_led

	bl copy_myself_to_sdram
	ldr r1, =on_the_ram
	add pc, r1, #0		@jump to sdram
	nop
	nop

on_the_ram:
	bl init_c_run_env
	bl dk_main

halt_loop:
	b halt_loop
	

disable_watchdog:
	ldr r0, =WTCON_ADDR
	mov r1, #0x0
	str r1, [r0]
	mov pc, lr

disable_interrupt:
	ldr r0, =INTCTL_BASE
	mov r1, #0xffffffff
	str r1, [r0, #oINTMSK]		@disable interrupts
	ldr r1, =0x7fff
	str r1, [r0, #oINTSUBMSK]	@disable sub interrupts
	mov pc, lr

@also disable caches for memory test!!!
disable_mmu:
	mrc p15, #0, r0, c1, c0, #0
	bic r0, r0, #0x01		@disable mmu
	@bic r0, r0, #0x1000		@disable ICache
	bic r0, r0, #0x4		@disable DCache
	mcr p15, #0, r0, c1, c0, #0
	mov pc, lr

init_sys_clk:
	@set locktime
	ldr r0, =CLKCTL_BASE
	mvn r1, #0xff000000		@r1 = 0x00ffffff
	str r1, [r0, #oLOCKTIME]

	@set CLKDIV, FCLK : HCLK: PCLK = 1 : 4 : 8 
	ldr r0, =CLKCTL_BASE
	mov r1, #5 			@=((2<<1) | (1<<0))
	str r1, [r0, #oCLKDIV]

	@set to asynchronous bus mode as HDIVN is not 0
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0xC0000000 	@#((1<<31) | (1 << 30))
	mcr p15, 0, r0, c1, c0, 0

	@set flck to 405MHZ
	ldr r0, =CLKCTL_BASE
	ldr r1, =MPLL_405MHZ
	str r1, [r0, #oMPLLCON]

	mov pc, lr

init_mem_ctl:
	ldr	r0, =MEMCTL_BASE
	add 	r3, r0, #4 * 13
	adrl 	r1, mem_cfg_vals
0:
	ldr	r2, [r1], #4
	str	r2, [r0], #4
	cmp	r0, r3
	bne	0b
	mov 	pc ,lr

.align 4
mem_cfg_vals:
	.long 0x22111110 @BWSCON: 0x22111110
	.long 0x00000700 @BANK0: default value
	.long 0x00000700 @BANK1: default value
	.long 0x00000700 @BANK2: default value
	.long 0x00000700 @BANK3: default value
	.long 0x00000700 @BANK4: default value
	.long 0x00000700 @BANK5: default value
	.long 0x00018005 @BANK6: RAS to CAS = 3(>2), CA(Clomun Address) = 9-bit
	.long 0x00018005 @BANK7: RAS to CAS = 3(>2), CA = 9-bit
	.long 0x008C04f5 @Refresh:en, auto, Trp=2, Trc=7, counter = 1269(HCLK=100MHz)
	.long 0x000000b1 @Busrt enabled, power down enabled, bank6/7 size:64MB
	.long 0x00000030 @MRSRB6: CL(CAS latency) = 3
	.long 0x00000030 @MRSRB7: CL = 3

@led1 <---> GPB5
@led2 <---> GPB6
@led3 <---> GPB7
@led4 <---> GPB8
init_led:
	ldr r0, =GPIOCTL_BASE
	ldr r1, =(1<<10 | 1<<12 | 1<<14 | 1<<16) @0x00015400	
	str r1, [r0, #oGPBCON]	@make GPB5,6,7,8 pin output

	ldr r1, =(1<<5 | 0<<6 | 1<<7 | 0<<8) @make GPB6,8 low to light on led2,4
	str r1, [r0, #oGPBDAT]

	mov pc, lr

@copy all the executable code to sdram
copy_myself_to_sdram:
#if 0
	mov r0, #0		@stepping stone
	ldr r1, =TEXT_BASE	@TEXT_BASE
	mov r2, #1024 * 4
copy_loop:
	ldr r3, [r0], #4
	str r3, [r1], #4
	cmp r0, r2
	bne copy_loop

	mov pc, lr
#endif
#if 0
	mov r10, lr		@save lr to r10 as we will call 2 fucntions later
	ldr sp, =DW_STACK_START
	mov fp, #0

	bl nand_init
	
	ldr r0, =TEXT_BASE
	mov r1, #0
	ldr r2, =TEXT_SIZE
	bl  nand_read

	mov pc, r10
#endif
#if 1
	mov r10, lr
	ldr sp, =DW_STACK_START
	mov fp, #0

	bl  load_program_from_nand

	mov pc, r10
#endif
	
init_c_run_env:
	ldr sp, =DW_STACK_START @
	@ldr sp, =0x34000000	@init stack pointer to the tail of 64MB 
	mov fp, #0		@no previous frame
	mov a2, #0		@set argv to NULL
	
	ldr r0, =bss_start
	ldr r1, =bss_end
	cmp r0, r1
	moveq pc, lr	

clean_loop:
	mov r2, #0
	str r2, [r0], #4
	cmp r0, r1
	bne clean_loop

	mov pc, lr
