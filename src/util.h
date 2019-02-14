#ifndef UTIL_H_
#define UTIL_H_

#include <cstdarg>

namespace util {
	int itoa(int value, char *buf, int base);
	int vsprintf(char *buf, const char *fmt, va_list args);
	int sprintf(char *buf, const char *fmt, ...);
}

#endif
