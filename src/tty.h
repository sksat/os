#ifndef TTY_H_
#define TTY_H_

#include "vram.h"
#include "util.h"

class Tty {
private:
	size_t x, y; // current pos
	VRAM::Base *vram;

public:
	using Color = VRAM::Color;

	Tty(VRAM::Base *vram) : x(0), y(0), vram(vram) {}

	void init(VRAM::Base *vram);

	void clear();
	void putchar(const char c);
	void puts(const char *str);
	void printf(const char *fmt, ...);

	void ok(){
		*this << Color::White << "\t["
			<< Color::Green << "ok"
			<< Color::White << "]\n";
	}
	void failed(){
		*this << Color::White << "\t["
			<< Color::Red << "failed"
			<< Color::White << "]";
	}

	Tty& operator<<(const Color &c){
		vram->set_color(static_cast<Color>(static_cast<uint8_t>(vram->color)>>4), c);
		return *this;
	}

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
