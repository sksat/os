#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "queue.h"

class Keyboard {
public:
	Keyboard(){
		keycode = queue<uint8_t,32>();
	}

	static void push_keycode(const uint8_t &kc){
		keycode.push(kc);
	}

	char get_char();
//private:
	static queue<uint8_t, 32> keycode;
};

extern "C" void int_handler21(int *esp);

#endif
