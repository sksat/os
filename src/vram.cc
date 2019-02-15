#include "vram.h"

using namespace VRAM;

void TextMode::clear(){
	for(size_t i=0;i<width*height*2;i++)
		*(vram+i) = 0;
}

void TextMode::putchar(const size_t x, const size_t y, const char c){
	auto addr = vram + (x + y * width)*2;
	*addr		= c;
	*(addr+1)	= static_cast<uint8_t>(color);
}
