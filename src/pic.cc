#include "pic.h"
#include "asmfunc.h"

using namespace asmfunc;

void PIC::init(){
	disable_all_int();

	out8(port::pic0_cmd, 0x11);	// ICW1: エッジトリガモード
	out8(port::pic0_data, 0x20);	// ICW2: IRQ0-7 -> INT20-27
	out8(port::pic0_data, 1 << 2);// ICW3: PIC1はIRQ2で接続
	out8(port::pic0_data, 0x01);	// ICW4: ノンバッファモード

	out8(port::pic1_cmd, 0x11);
	out8(port::pic1_data, 0x28);	// ICW2: IRQ8-15 -> INT28-2f
	out8(port::pic1_data, 2);		// ICW3: PIC1はIRQ2で接続
	out8(port::pic1_data, 0x01);

	out8(port::pic0_data, 0xfb);
	out8(port::pic1_data, 0xff);
}

void PIC::disable_all_int(){
	out8(port::pic0_data, 0xff);
	out8(port::pic1_data, 0xff);
}

void PIC::set_mask(uint16_t mask){
	mask = ~mask;
	out8(port::pic0_data, mask & 0xff);
	out8(port::pic1_data, (mask>>8) & 0xff);
}
