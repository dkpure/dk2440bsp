#ifndef _S3C2440_REGS_H
#define _S3C2440_REGS_H

#define __REG(r)	(*(volatile unsigned long *) (r))
#define __REG8(r)	(*(volatile unsigned char *) (r))

/*
 *watchdog
 */
#define WTCON_ADDR	0x53000000
#define reg_WTCON	__REG(WTCON_ADDR)

/*
 *interrupt
 */
#define INTCTL_BASE	0x4A000000
#define oSRCPND		0x00
#define oINTMOD		0x04
#define oINTMSK		0x08
#define oPRIO		0x0C
#define oINTPND		0x10
#define oINTOFFSET	0x14
#define oSUBSRCPND	0x18
#define oINTSUBMSK	0x1C

#define reg_SRCPND	__REG(INTCTL_BASE + oSRCPND)

/*
 *system clock
 */
#define CLKCTL_BASE	0x4C000000
#define oLOCKTIME	0x00
#define oMPLLCON	0x04
#define oUPLLCON	0x08
#define oCLKCON		0x0C
#define oCLKSLOW	0x10
#define oCLKDIV		0x14
#define oCAMDIVN	0x18

/*
 *memory controller
 */
#define MEMCTL_BASE	0x48000000
#define oBWSCON		0x00
#define oBANKCON0	0x04
#define oBANKCON1	0x08
#define oBANKCON2	0x0C
#define oBANKCON3	0x10
#define oBANKCON4	0x14
#define oBANKCON5	0x18
#define oBANKCON6	0x1C
#define oBANKCON7	0x20
#define oREFRESH	0x24
#define oBANKSIZE	0x28
#define oMRSRB6		0x2C
#define oMRSRB7		0x30

/*
 *gpio
 */
#define GPIOCTL_BASE	0x56000000
#define oGPACON		0x00
#define oGPADAT		0x04
/* reserved		0x08 */
/* reserved		0x0C */
#define reg_GPACON	__REG(GPIOCTL_BASE + oGPACON)
#define reg_GPADAT	__REG(GPIOCTL_BASE + oGPADAT)

#define oGPBCON		0x10
#define oGPBDAT		0x14
#define oGPBUP		0x18
/* reserved		0x1C */
#define reg_GPBCON	__REG(GPIOCTL_BASE + oGPBCON)
#define reg_GPBDAT	__REG(GPIOCTL_BASE + oGPBDAT)
#define reg_GPBUP	__REG(GPIOCTL_BASE + oGPBUP )

#define oGPCCON		0x20
#define oGPCDAT		0x24
#define oGPCUP		0x28
/* reserved		0x2C */
#define reg_GPCCON	__REG(GPIOCTL_BASE + oGPCCON)
#define reg_GPCDAT	__REG(GPIOCTL_BASE + oGPCDAT)
#define reg_GPCUP	__REG(GPIOCTL_BASE + oGPCUP )

#define oGPDCON		0x30
#define oGPDDAT		0x34
#define oGPDUP		0x38
/* reserved		0x3C */
#define reg_GPDCON	__REG(GPIOCTL_BASE + oGPDCON)
#define reg_GPDDAT	__REG(GPIOCTL_BASE + oGPDDAT)
#define reg_GPDUP	__REG(GPIOCTL_BASE + oGPDUP )

#define oGPECON		0x40
#define oGPEDAT		0x44
#define oGPEUP		0x48
/* reserved		0x4C */
#define reg_GPECON	__REG(GPIOCTL_BASE + oGPECON)
#define reg_GPEDAT	__REG(GPIOCTL_BASE + oGPEDAT)
#define reg_GPEUP	__REG(GPIOCTL_BASE + oGPEUP )

#define oGPFCON		0x50
#define oGPFDAT		0x54
#define oGPFUP		0x58
/* reserved		0x5C */
#define reg_GPFCON	__REG(GPIOCTL_BASE + oGPFCON)
#define reg_GPFDAT	__REG(GPIOCTL_BASE + oGPFDAT)
#define reg_GPFUP	__REG(GPIOCTL_BASE + oGPFUP )

#define oGPGCON		0x60
#define oGPGDAT		0x64
#define oGPGUP		0x68
#define reg_GPGCON	__REG(GPIOCTL_BASE + oGPGCON)
#define reg_GPGDAT	__REG(GPIOCTL_BASE + oGPGDAT)
#define reg_GPGUP	__REG(GPIOCTL_BASE + oGPGUP )

#define oGPHCON		0x70
#define oGPHDAT		0x74
#define oGPHUP		0x78
/* reserved		0x7C */
#define reg_GPHCON	__REG(GPIOCTL_BASE + oGPHCON)
#define reg_GPHDAT	__REG(GPIOCTL_BASE + oGPHDAT)
#define reg_GPHUP	__REG(GPIOCTL_BASE + oGPHUP )

#define oGPJCON		0xD0
#define oGPJDAT		0xD4
#define oGPJUP		0xD8
/* reserved		0xDC */
#define reg_GPJCON	__REG(GPIOCTL_BASE + oGPJCON)
#define reg_GPJDAT	__REG(GPIOCTL_BASE + oGPJDAT)
#define reg_GPJUP	__REG(GPIOCTL_BASE + oGPJUP )

/* MISCCR 	ignored */
/* DCLKCON 	ignored */

#define oEXTINT0	0x88
#define oEXTINT1	0x8C
#define oEXTINT2	0x90

/* EINTFLT0	ignored */
/* EINTFLT1	ignored */
/* EINTFLT2	ignored */
/* EINTFLT3	ignored */

#define oEINTMASK	0xA4
#define oEINTPEND	0xA8

/* General Status Registers */
#define oGSTATUS0	0xAC
#define oGSTATUS1	0xB0
#define oGSTATUS2	0xB4
#define oGSTATUS3	0xB8
#define oGSTATUS4	0xBC

/* DSC0		ignored */
/* DSC1		ignored */
/* MSLCON	ignored */

/*
 *UART
 */
#define UART0_CTL_BASE	0x50000000
#define UART1_CTL_BASE	0x50004000
#define UART2_CTL_BASE	0x50008000

#define oULCON		0x00
#define oUCON		0x04
#define oUFCON		0x08
#define oUMCON		0x0C
#define oUTRSTAT	0x10
#define oUERSTAT	0x14
#define oUFSTAT		0x18
#define oUMSTAT		0x1C
#define oUTXH_LE	0x20
#define oUTXH_BE	0x23
#define oURXH_LE	0x24
#define oURXH_BE	0x27
#define oUBRDIV		0x28

#define reg_ULCON0	__REG(UART0_CTL_BASE + oULCON)
#define reg_UCON0	__REG(UART0_CTL_BASE + oUCON)
#define reg_UFCON0	__REG(UART0_CTL_BASE + oUFCON)
#define reg_UMCON0	__REG(UART0_CTL_BASE + oUMCON)
#define reg_UTRSTAT	__REG(UART0_CTL_BASE + oUTRSTAT)
#define reg_UERSTAT	__REG(UART0_CTL_BASE + oUERSTAT)
#define reg_UFSTAT	__REG(UART0_CTL_BASE + oUFSTAT)
#define reg_UMSTAT	__REG(UART0_CTL_BASE + oUMSTAT)
#define reg_UTXH_LE	__REG(UART0_CTL_BASE + oUTXH_LE)
#define reg_URXH_LE	__REG(UART0_CTL_BASE + oURXH_LE)
#define reg_UBRDIV	__REG(UART0_CTL_BASE + oUBRDIV)

/*
 * NandFlash controller
 */
#define NAND_CTL_BASE	0x4E000000
#define oNFCONF		0x00
#define oNFCONT		0x04
#define oNFCMMD		0x08
#define oNFADDR		0x0C
#define oNFDATA		0x10
#define oNFMECCD0	0x14
#define oNFMECCD1	0x18
#define oNFMECCD	0x1C
#define oNFSTAT		0x20
#define oNFESTAT0	0x24
#define oNFESTAT1	0x28
#define oNFMECC0	0x2C
#define oNFMECC1	0x30
#define oNFSECC		0x34
#define oNFSBLK		0x38
#define oNFEBLK		0x3C

#define reg_NFCONF	__REG(NAND_CTL_BASE + oNFCONF)
#define reg_NFCONT	__REG(NAND_CTL_BASE + oNFCONT)
#define reg_NFCMMD	__REG8(NAND_CTL_BASE + oNFCMMD)
#define reg_NFADDR	__REG8(NAND_CTL_BASE + oNFADDR)
#define reg_NFDATA	__REG8(NAND_CTL_BASE + oNFDATA)	/* 8-bit register! */
#define reg_NFMECCD0	__REG(NAND_CTL_BASE + oNFMECCD0)
#define reg_NFMECCD1	__REG(NAND_CTL_BASE + oNFMECCD1)
#define reg_NFMECCD	__REG(NAND_CTL_BASE + oNFMECCD)
#define reg_NFSTAT	__REG(NAND_CTL_BASE + oNFSTAT)
#define reg_NFESTAT0	__REG(NAND_CTL_BASE + oNFESTAT0)
#define reg_NFESTAT1	__REG(NAND_CTL_BASE + oNFESTAT1)
#define reg_NFMECC0	__REG(NAND_CTL_BASE + oNFMECC0)
#define reg_NFMECC1	__REG(NAND_CTL_BASE + oNFMECC1)
#define reg_NFMECC	__REG(NAND_CTL_BASE + oNFMECC)
#define reg_NFSBLK	__REG(NAND_CTL_BASE + oNFSBLK)
#define reg_NFEBLK	__REG(NAND_CTL_BASE + oNFEBLK)


#endif
