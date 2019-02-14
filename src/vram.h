#ifndef VRAM_H_
#define VRAM_H_

#include <cstddef>
#include "common.h"

namespace VRAM {
	class Base {
	protected:
		addr_t vram;
		size_t width, height;
	public:
		Base(const addr_t addr, const size_t w, const size_t h) : vram(addr), width(w), height(h) {}

		size_t get_width() const { return width; }
		size_t get_height()const { return height;}

		virtual void clear() = 0;
		virtual void putchar(const size_t x, const size_t y, const char c) = 0;
	};

	class TextMode : public Base {
	public:
		TextMode(const addr_t addr, const size_t w, const size_t h) : Base(addr,w,h) {}

		void clear();
		void putchar(const size_t x, const size_t y, const char c);
	};

	class GraphicMode : public Base {
		void clear();
	};
}

#endif
