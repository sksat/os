KERNEL	= kernel.bin
OBJS	= boot.o main.o vram.o tty.o util.o

CC		= gcc
CXX		= g++
LD		= ld

CFLAGS	=
CXXFLAGS= -std=c++17 -m32 -O0 -g -Wall -Wextra \
		  -ffreestanding -fno-builtin -fno-exceptions -fno-rtti -fomit-frame-pointer
LDFLAGS	= -melf_i386 -T linker.ld -n

%.o:%.S
	$(CC) -m32 -c $< -o $@

%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o:%.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# command

default:
	make $(KERNEL)

run:
	make -C .. run

clean:
	rm -f $(KERNEL)
	rm -f *.o

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
