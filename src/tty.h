#ifndef TTY_H_
#define TTY_H_

#include "vram.h"
#include "util.h"

class Tty {
private:
	size_t x, y; // current pos
	VRAM::Base *vram;

public:
	Tty() : x(0), y(0), vram(nullptr) {}

	void init(VRAM::Base *vram);

	void clear();
	void putchar(const char c);
	void puts(const char *str);
	void printf(const char *fmt, ...);
};

#endif
