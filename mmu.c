#include "mmu.h"
#include "configs.h"

static unsigned long *mmu_tlb_base = (unsigned long *) MMU_TABLE_BASE;

/*
 * cpu_arm920_cache_clean_invalidate_all()
 *
 * clean and invalidate all cache lines
 *
 */
static inline void cpu_arm920_cache_clean_invalidate_all(void)
{
__asm__(
	"	mov	r1, #0\n"
	"	mov	r1, #7 << 5\n"		  /* 8 segments */
	"1:	orr	r3, r1, #63 << 26\n"	  /* 64 entries */
	"2:	mcr	p15, 0, r3, c7, c14, 2\n" /* clean & invalidate D index */
	"	subs	r3, r3, #1 << 26\n"
	"	bcs	2b\n"			  /* entries 64 to 0 */
	"	subs	r1, r1, #1 << 5\n"
	"	bcs	1b\n"			  /* segments 7 to 0 */
	"	mcr	p15, 0, r1, c7, c5, 0\n"  /* invalidate I cache */
	"	mcr	p15, 0, r1, c7, c10, 4\n" /* drain WB */
	);
}

void cache_clean_invalidate(void)
{
	cpu_arm920_cache_clean_invalidate_all();
}

/*
 * cpu_arm920_tlb_invalidate_all()
 *
 * Invalidate all TLB entries
 */
static inline void cpu_arm920_tlb_invalidate_all(void)
{
	__asm__(
		"mov	r0, #0\n"
		"mcr	p15, 0, r0, c7, c10, 4\n"	/* drain WB */
		"mcr	p15, 0, r0, c8, c7, 0\n"	/* invalidate I & D TLBs */
		);
}

void tlb_invalidate(void)
{
	cpu_arm920_tlb_invalidate_all();
}

/* as linear mapping, va equals to pa */
static void mem_mapping_linear(void)
{
	unsigned long va, pa, i;
	va = 0;
	pa = 0;
	
	/* first mapping the total supported 4GB pa to va, 
	 * non-cacheable, non-bufferable
	 */
	for (i = 0; i < 4096; ++i) {
		va = pa = i << 20;
		/**(mmu_tlb_base + va >> 20) = (pa & 0xFFF00000) | MMU_SECDESC_NORMAL;*/
		mmu_tlb_base[va >> 20] = (pa & 0xFFF00000) | MMU_SECDESC_NORMAL;
	}

	/* then make sdram cacheable */
	for (i = SDRAM_BASE; i < (SDRAM_BASE + SDRAM_SIZE); i += SZ_1M) {
		/**(mmu_tlb_base + i >> 20) = (i & 0xFFF00000) | MMU_SECDESC_WB;*/
		/**(mmu_tlb_base + (i >> 20)) = (i & 0xFFF00000) | MMU_SECDESC_NORMAL | MMU_CACHEABLE;*/
		mmu_tlb_base[i >> 20] = (i & 0xFFF00000) | MMU_SECDESC_NORMAL | MMU_CACHEABLE;
	}
}

static inline void cpu_arm920_mmu_init(void)
{
	unsigned long ttb = MMU_TABLE_BASE;

__asm__(
	/* Invalidate caches */
	"mov	r0, #0\n"
	"mcr	p15, 0, r0, c7, c7, 0\n"	/* invalidate I,D caches on v4 */
	"mcr	p15, 0, r0, c7, c10, 4\n"	/* drain write buffer on v4 */
	"mcr	p15, 0, r0, c8, c7, 0\n"	/* invalidate I,D TLBs on v4 */
	/* Load page table pointer */
	"mov	r4, %0\n"
	"mcr	p15, 0, r4, c2, c0, 0\n"	/* load page table pointer */
	/* Write domain id (cp15_r3) */
	"mvn	r0, #0\n"			/* Domains 0, 1 = client */
	"mcr	p15, 0, r0, c3, c0, 0\n"	/* load domain access register */
	/* Set control register v4 */
	"mrc	p15, 0, r0, c1, c0, 0\n"	/* get control register v4 */
	/* Clear out 'unwanted' bits (then put them in if we need them) */
						/* .RVI ..RS B... .CAM */ 
	"bic	r0, r0, #0x3000\n"		/* ..11 .... .... .... */
	"bic	r0, r0, #0x0300\n"		/* .... ..11 .... .... */
	"bic	r0, r0, #0x0087\n"		/* .... .... 1... .111 */
	/* Turn on what we want */
	/* Fault checking enabled */
	"orr	r0, r0, #0x0002\n"		/* .... .... .... ..1. */
	/* D-Cahce on*/
	"orr	r0, r0, #0x0004\n"		/* .... .... .... .1.. */
	/* I-Cache on */
	"orr	r0, r0, #0x1000\n"		/* ...1 .... .... .... */
	/* MMU enabled */
	"orr	r0, r0, #0x0001\n"		/* .... .... .... ...1 */

	"mcr	p15, 0, r0, c1, c0, 0\n"	/* write control register */
	: /* no outputs */
	: "r" (ttb) );
}

void mmu_init(void)
{
	cpu_arm920_mmu_init();
}

void mem_map(void)
{
	mem_mapping_linear();
	cache_clean_invalidate();
	tlb_invalidate();
}
