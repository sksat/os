#include "multiboot2.h"

#define VRAM		0xB8000
#define COLUMNS		80
#define LINES		24
#define ATTRIBUTE	7

class TextMode {
public:
	volatile unsigned char *vram;
	int x=0, y=0;

	void clear();
	void putchar(const unsigned int x, const unsigned int y, const char c);
	void putchar(const char c){ putchar(x,y,c); }
	void puts(const char *str);
};

extern "C" void kmain(unsigned long magic, unsigned long addr){
	TextMode tty;
	tty.vram = (unsigned char*) VRAM;

	tty.clear();
	tty.puts("hello");

	while(1);
	return;
}

void TextMode::clear(){
	for(int i=0;i<COLUMNS*LINES*2;i++)
		*(vram+i) = 0;
}

void TextMode::putchar(const unsigned int x, const unsigned int y, const char c){
	auto addr = vram + (x + y * COLUMNS)*2;
	*addr = c & 0xff;
	*(addr+1) = ATTRIBUTE;
}

void TextMode::puts(const char *str){
	for(int i=0;;i++){
		if(str[i] == '\t')
			x+=4;
		else if(str[i] == '\n')
			y++;
		else if(str[i] == '\0')
			break;
		else{
			putchar(str[i]);
			x++;
		}
	}
}
