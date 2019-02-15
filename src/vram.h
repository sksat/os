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
		Base() : vram(0x00), width(0), height(0) {}

		void init(addr_t vram, size_t width, size_t height){
			this->vram	= vram;
			this->width	= width;
			this->height= height;
		}

		size_t get_width() const { return width; }
		size_t get_height()const { return height;}

		virtual void clear() = 0;
		virtual void putchar(const size_t x, const size_t y, const char c) = 0;
	};

	class TextMode : public Base {
	public:
		void clear();
		void putchar(const size_t x, const size_t y, const char c);
	};

	class GraphicMode : public Base {
		void clear();
	};
}

#endif
