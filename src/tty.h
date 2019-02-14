#ifndef TTY_H_
#define TTY_H_

#include "vram.h"

class Tty {
private:
	size_t x, y; // current pos
	VRAM::Base *vram;

public:
	explicit Tty(VRAM::Base *vram) : vram(vram) {}

	void clear();
	void putchar(const char c);
	void puts(const char *str);
};

#endif
