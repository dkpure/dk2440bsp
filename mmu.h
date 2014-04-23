#ifndef _MMU_H
#define _MMU_H

#define MMU_FULL_ACCESS		(3 << 10)	/* access permission */
#define MMU_DOMAIN		(0 << 5)	/* belong to which domain */
#define MMU_SPECIAL		(1 << 4)	/* must be 1 */
#define MMU_CACHEABLE		(1 << 3)	/* cacheable */
#define MMU_BUFFERABLE		(1 << 2)	/* bufferable */
#define MMU_SECTION		(2)		/* section descripter */
#define MMU_SECDESC_NORMAL	(MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
#define MMU_SECDESC_WB		(MMU_SECDESC_NORMAL | MMU_CACHEABLE | MMU_BUFFERABLE)
#define MMU_SECTION_SIZE	0x00100000


extern void mem_map(void);
extern void mmu_init(void);
#endif
