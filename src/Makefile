KERNEL	= kernel.bin
OBJS	= boot.o

CC		= gcc
LD		= ld

%.o:%.S
	$(CC) -c $< -o $@

%.o:%.c
	$(CC) -c $< -o $@

# command

default:
	make $(KERNEL)

clean:
	rm -f $(KERNEL)
	rm -f *.o

kernel.bin: $(OBJS)
	$(LD) -n -o $@ -T linker.ld $^
