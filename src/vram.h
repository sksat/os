#ifndef VRAM_H_
#define VRAM_H_

#include <cstddef>
#include "common.h"

namespace VRAM {
	enum class Color : uint8_t {
		Black = 0x0,
		Blue,
		Green,
		Cyan,
		Red,
		Magenta,
		Brown,
		LightGray,
		DarkGray,
		LightBlue,
		LightGreen,
		LightCyan,
		LightRed,
		LightMagenta,
		LightBrown,
		White
	};

	class Base {
	protected:
		addr_t vram;
		size_t width, height;
	public:
		Color color;

		Base() : vram(0x00), width(0), height(0) {
			set_color(Color::Black, Color::White);
		}

		void init(addr_t vram, size_t width, size_t height){
			this->vram	= vram;
			this->width	= width;
			this->height= height;
		}

		size_t get_width() const { return width; }
		size_t get_height()const { return height;}

		void set_color(Color c){ color=c; }
		void set_color(Color back, Color fore){
			color= static_cast<Color>((static_cast<uint8_t>(back)<<4) | (static_cast<uint8_t>(fore)&0x0f));
		} // for text mode

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
