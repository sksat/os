KERNEL	= kernel.bin
OBJS	= boot.o main.o

CC		= gcc
CXX		= g++
LD		= ld

CFLAGS	=
CXXFLAGS= -fno-builtin -nostdinc -O -g -Wall

%.o:%.S
	$(CC) -c $< -o $@

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
	$(LD) -n -o $@ -T linker.ld $^
