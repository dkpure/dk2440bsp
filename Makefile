CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy
LDFLAGS=-Tmem.lds -Bstatic -nostdlib
LIBPATH=-lgcc -L/home/pure/work/mini2440/arm/4.3.2/lib/gcc/arm-none-linux-gnueabi/4.3.2

all:	core_init.o main.o mmu.o nandflash.o no_raise_fixed.o
	$(LD) $(LDFLAGS)  $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S a.out dk2440bsp.bin -R .comment -R .stab -R .stabstr
	rm *.o a.out

%.o : %.S
	$(CC) -mabi=aapcs-linux -mno-thumb-interwork -Os -Wall -c $^

%.o : %.c
	$(CC) -mabi=aapcs-linux -mno-thumb-interwork -Os -Wall -c $^

.PHONY:clean
clean:
	rm *.bin
