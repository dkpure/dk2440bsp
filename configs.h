#ifndef _CONFIGS_H
#define _CONFIGS_H

#define SZ_1K                           0x00000400
#define SZ_4K                           0x00001000
#define SZ_8K                           0x00002000
#define SZ_16K                          0x00004000
#define SZ_32K				0x00008000
#define SZ_64K                          0x00010000
#define SZ_128K                         0x00020000
#define SZ_256K                         0x00040000
#define SZ_512K                         0x00080000

#define SZ_1M                           0x00100000
#define SZ_2M                           0x00200000
#define SZ_4M                           0x00400000
#define SZ_8M                           0x00800000
#define SZ_16M                          0x01000000
#define SZ_32M                          0x02000000
#define SZ_64M                          0x04000000
#define SZ_128M                         0x08000000
#define SZ_256M                         0x10000000
#define SZ_512M                         0x20000000

#define SZ_1G                           0x40000000
#define SZ_2G                           0x80000000

/*
 * sdram partition
 *  +-------------+
 *  |	text      |	2M
 *  ---------------
 *  |	heap	  |	2M
 *  ---------------
 *  |	mmu table |	16K
 *  ---------------
 *  |	stack	  |	512K
 *  ---------------
 *  |	free ram  |	64M - 2M - 2M - 16K - 512K
 *  +-------------+
 * */
#define SDRAM_BASE	0x30000000
#define SDRAM_SIZE	SZ_64M
#define TEXT_SIZE	SZ_2M
#define TEXT_BASE	(SDRAM_BASE + SDRAM_SIZE - TEXT_SIZE) /* 0x33E00000 */
#define HEAP_SIZE	SZ_2M
#define HEAP_BASE	(TEXT_BASE - HEAP_SIZE)
#define MMU_TABLE_SIZE	SZ_16K
#define MMU_TABLE_BASE	(HEAP_BASE - MMU_TABLE_SIZE)
#define STACK_SIZE	SZ_512K
#define STACK_BASE	(MMU_TABLE_BASE - STACK_SIZE)
#define FREE_RAM_SIZE	(STACK_BASE - SDRAM_BASE)
#define FREE_RAM_BASE	SDRAM_BASE

#define DW_STACK_START	(STACK_BASE + STACK_SIZE - 4)

#define FIN	12000000
/*
Caution: MPLL_400MHZ is fit the equation of Fout, it not works properly
in fact and I donot know why.
#define MPLL_400MHZ 	((92<<12) | (1<<4) | (0<<0))
*/
#define MPLL_405MHZ	((127<<12) | (2<<4) | (1<<0))
#define FCLK		405000000
#define HCLK		101250000
#define PCLK		50625000

#define vUART_BAUD_RATE	115200
#define vUBRDIVn	((PCLK / (vUART_BAUD_RATE * 16)) - 1)
#define vUART_GPIO_CON	0xaaa
#define vUART_GPIO_UP	0x7ff

#define NAND_TACLS	1//7
#define NAND_TWRPH0	2//7
#define NAND_TWRPH1	0//7

#endif
