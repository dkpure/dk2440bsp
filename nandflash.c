#include "nandflash.h"
#include "s3c2440_regs.h"
#include "configs.h"

#define NF_SELECT()		do {reg_NFCONT &= (~(1<<1));} while(0)
#define NF_DESELECT()		do {reg_NFCONT |= (1<<1);} while(0)
#define NF_CMD(c)		do {reg_NFCMMD = c; } while(0)
#define NF_ADDR(d)		do {reg_NFADDR = d; } while(0)
#define NF_DATA			(reg_NFDATA)
/* clear RB pin manually before detect it */
#define NF_CLEAR_RB()		do {reg_NFSTAT |= (1<<2);} while(0)
#define NF_DETECT_RB()		while (!(reg_NFSTAT & (1<<2)))

static inline void nand_reset(void)
{
	NF_SELECT();
	NF_CLEAR_RB();
	NF_CMD(NF_CODE_RESET);
	NF_DETECT_RB();
	NF_DESELECT();
}

void nand_init(void)
{
	reg_NFCONF = (NAND_TACLS << 12) | (NAND_TWRPH0 << 8) | (NAND_TWRPH1 << 4);
	reg_NFCONT = (1 << 4) | (1 << 1) | (1 << 0);
	reg_NFSTAT = 0;
	nand_reset();
	/*nand_check_id();*/
}

/* if the 2049th byte of the first page in one block equals to 0xFF, then this
 * is a good block, otherwise a bad block.
 */
static int nand_isbadblock_p2048(unsigned int block)
{
	unsigned int page;
	int bad = 0;

	page = block << NF_BLOCK_PAGE_SHIFT; /* 1 block has 64 pages */
	NF_SELECT();
	NF_CLEAR_RB();

	NF_CMD(NF_CODE_READ0);
	NF_ADDR(2048 & 0xFF);
	NF_ADDR((2048 >> 8) & 0xFF);
	NF_ADDR(page & 0xFF);
	NF_ADDR((page >> 8) & 0xFF);
	NF_ADDR((page >> 16) & 0xFF);
	NF_CMD(NF_CODE_READ1);
	
	NF_DETECT_RB();	
	bad = NF_DATA;
	NF_DESELECT();
	return (bad != 0xFF);
}

/* copy  <size> bytes from <start_addr> to ram<buf> */
void nand_read(unsigned char *buf, unsigned long start_addr, unsigned long size)
{
	int i, j;

	NF_SELECT();

	for (i = start_addr; i < start_addr + size; ) {
		NF_CLEAR_RB();

		NF_CMD(NF_CODE_READ0);
		NF_ADDR(i & 0xFF);
		NF_ADDR((i >> 8) & 0xFF);
		NF_ADDR((i >> 11) & 0xFF);
		NF_ADDR((i >> 19) & 0xFF);
		NF_ADDR((i >> 27) & 0xFF);
		NF_CMD(NF_CODE_READ1);

		NF_DETECT_RB();

		for (j = 0; j < NF_PAGE_SIZE; ++j, ++i) {
			*buf++ = NF_DATA & 0xFF;
		}
	}

	NF_DESELECT();
}

static void nand_read_page2048(unsigned int page, unsigned char *buf)
{
	unsigned int i;
	unsigned int *word_buf = (unsigned int *)buf;
	unsigned int word32;

	NF_SELECT();
	NF_CLEAR_RB();

	NF_CMD(NF_CODE_READ0);
	NF_ADDR(0x00);
	NF_ADDR(0x00);
	NF_ADDR(page & 0xFF);
	NF_ADDR((page >> 8) & 0xFF);
	NF_ADDR((page >> 16) & 0xFF);
	NF_CMD(NF_CODE_READ1);

	NF_DETECT_RB();

	/*
	for (i = 0; i < NF_PAGE_SIZE; ++i)
		*buf++ = NF_DATA & 0xFF;
	*/
	/* use word access to speed up the copy procedure */
	for (i = 0; i < (NF_PAGE_SIZE >> 2); ++i) {
		word32 = NF_DATA;
		word32 |= (NF_DATA << 8);
		word32 |= (NF_DATA << 16);
		word32 |= (NF_DATA << 24);
		*word_buf++ = word32;
	}

	NF_DESELECT();
}

#define begin_of_block(p)	(((p) & ((1 << NF_BLOCK_PAGE_SHIFT) - 1)) == 0)
/*
 *copy <TEXT_SIZE> bytes from address 0 of nandflash to <TEXT_BASE> of sdram
 */
void load_program_from_nand(void)
{
	unsigned int i, pages, goodpages;
	unsigned char *program_addr = (unsigned char*) TEXT_BASE;
	unsigned long *ptr;

	pages = TEXT_SIZE >> NF_PAGE_SHIFT;

	nand_init();
	for (i = 0, goodpages = 0; goodpages < pages; ) {
		if (begin_of_block(i)) {
			if (nand_isbadblock_p2048(i>>NF_BLOCK_PAGE_SHIFT)) {
				i += NF_BLOCK_NPAGES;
				continue;
			}
		}	

		/*nand_read_page2048(i, program_addr + i << NF_PAGE_SHIFT);*/
		nand_read_page2048(i, program_addr + (goodpages << NF_PAGE_SHIFT));

		++i;
		++goodpages;
	}

	ptr = (unsigned long *)0x30000000;
	*ptr++ = goodpages;
	*ptr++ = i;
	*ptr = pages;
}
