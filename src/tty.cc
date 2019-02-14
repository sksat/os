#include "tty.h"

void Tty::clear(){
	vram->clear();
	x = 0;
	y = 0;
}

void Tty::putchar(const char c){
	if(x >= vram->get_width()-1){
		x = 0;
		y++;
	}

	if(y >= vram->get_height()-1)
		clear();

	switch(c){
	case '\t':
		x+=4;
		break;
	case '\n':
		x=0;
		y++;
		break;
	default:
		vram->putchar(x, y, c);
		x++;
		break;
	}
}

void Tty::puts(const char *str){
	for(size_t i=0;;i++){
		if(str[i]=='\0') break;
		putchar(str[i]);
	}
}

void Tty::printf(const char *fmt, ...){
	va_list ap;
	char buf[160];

	va_start(ap, fmt);
	util::vsprintf(buf, fmt, ap);
	va_end(ap);

	puts(buf);
}
