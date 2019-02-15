#ifndef TTY_H_
#define TTY_H_

#include "vram.h"
#include "util.h"

class Tty {
private:
	size_t x, y; // current pos
	VRAM::Base *vram;

public:
	Tty(VRAM::Base *vram) : x(0), y(0), vram(vram) {}

	void init(VRAM::Base *vram);

	void clear();
	void putchar(const char c);
	void puts(const char *str);
	void printf(const char *fmt, ...);

	Tty& operator<<(const char &c){
		putchar(c);
		return *this;
	}
	Tty& operator<<(const char *str){
		puts(str);
		return *this;
	}
	Tty& operator<<(const int val){
		printf("%d", val);
		return *this;
	}
	Tty& operator<<(const uint32_t val){
		printf("%d", val);
		return *this;
	}
	Tty& operator<<(const uint64_t val){
		printf("%x", val);
		return *this;
	}
};

#endif
