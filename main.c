#include "s3c2440_regs.h"
#include "configs.h"
#include "mmu.h"
#include "nandflash.h"

#include <stdio.h>

static void delay(volatile unsigned long dly)
{
	for (; dly != 0; --dly);
}

void init_uart(void)
{
	reg_ULCON0 = 3;		//8bits, 1 stop bit, no parity, normal mode
	reg_UCON0  = 4;		//use PCLK as UART Clock, disable rx, enable tx
	reg_UFCON0 = 0;		//disable fifo
	reg_UMCON0 = 0;		//disable modem
	reg_UBRDIV = vUBRDIVn;	//set badurate div

	//also init gpios of uart0
	reg_GPHCON = vUART_GPIO_CON;
	reg_GPHUP = vUART_GPIO_UP;
}

static void uart_send_byte(char ch)
{
	//check transmitter empty
	while (!(reg_UTRSTAT & 4))
		;

	reg_UTXH_LE = ch;
}

void uart_send_str(char *str)
{
	if (NULL == str)
		return;

	while (*str != '\0') {
		uart_send_byte(*str++);
	}
}

void uart_send_u8(unsigned char n)
{
	static char hex_assic_table[] = "0123456789ABCDEF";
	unsigned char m;
	
	m = n >> 4;
	uart_send_byte(hex_assic_table[m & 15]); /* m % 16 = m & (16 -1) */
	uart_send_byte(hex_assic_table[n & 15]);

}

/* 32bit division has some problem! */
void uart_send_hex(unsigned int n)
{
	unsigned char b1, b2, b3, b4;
	
	b1 = n & 0xFF;
	b2 = (n >>8) & 0xFF;
	b3 = (n >>16) & 0xFF;
	b4 = (n >>24) & 0xFF;

	uart_send_u8(b4);
	uart_send_u8(b3);
	uart_send_u8(b2);
	uart_send_u8(b1);
}

int dk_main(void)
{
	unsigned long *ptr;

	init_uart();
	uart_send_str("\r\r\n>>In dk_main now!");

	ptr = (unsigned long *)0x30000000;
	uart_send_str("\r\nglobal_pages = ");
	uart_send_hex(*ptr);
	++ptr;
	uart_send_str("\r\nglobal_i = ");
	uart_send_hex(*ptr);
	++ptr;
	uart_send_str("\r\npages = ");
	uart_send_hex(*ptr);

	/*
	 * memory mapping
	 */
#define USE_MMU
#ifdef USE_MMU
	mem_map();
	mmu_init();
	uart_send_str("\r\n>>memory mapping succeed!");
#endif

	while (1) {
		reg_GPBDAT = 0x140;
#ifdef USE_MMU
		delay(300000); delay(300000); delay(300000); delay(300000);
		delay(300000); delay(300000); delay(300000); delay(300000);
		delay(300000); delay(300000); delay(300000); delay(300000);
		delay(300000); delay(300000); delay(300000); delay(300000);
#else
		delay(300000);
#endif
		reg_GPBDAT = 0xa0;
#ifdef USE_MMU
		delay(300000); delay(300000); delay(300000); delay(300000);
		delay(300000); delay(300000); delay(300000); delay(300000);
		delay(300000); delay(300000); delay(300000); delay(300000);
		delay(300000); delay(300000); delay(300000); delay(300000);
#else
		delay(300000);
#endif
	}

	return 0;
}
