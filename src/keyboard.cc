#include "keyboard.h"
#include "pic.h"
#include "asmfunc.h"

queue<uint8_t, 32> Keyboard::keycode;

extern "C" void int_handler21(int *esp){
	asmfunc::out8(PIC::port::pic0_cmd, 0x60 + 1); // IRQ1受付終了
	uint8_t data = asmfunc::in8(0x60); // keyboard=0x60
	Keyboard::push_keycode(data);
}

constexpr char table[0x54] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '^', 0, 0,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '@', '[', 0, 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', ':', 0, 0, ']',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6',
	'+', '1', '2', '3', '0', '.',
};

char Keyboard::get_char(){
	if(keycode.empty())
		return '\0';
	auto code = keycode.pop();
	if(code < 0x54)
		return table[code];
	else
		return '\0';
}
