#ifndef _NANDFLASH_H
#define _NANDFLASH_H

/* NandFlash K9F1G08U0B: 128MB
 * 1 device = 1024 block2
 * 1 block = 64 pages
 * 1 page = (2K + 64)bytes
 */

#define NF_BLOCK_PAGE_SHIFT	6	/* 2^6 = 64 */
#define NF_BLOCK_NPAGES		(1 << NF_BLOCK_PAGE_SHIFT)
#define NF_PAGE_SHIFT		11	/* 2^11 = 2048 */
#define NF_PAGE_SIZE		(1 << NF_PAGE_SHIFT)

#define NF_CODE_RESET	0xFF
#define NF_CODE_READ0	0x00
#define NF_CODE_READ1	0x30

extern void nand_init(void);
extern void nand_read(unsigned char *buf, unsigned long start_addr, unsigned long size);

#endif
