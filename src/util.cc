#include "util.h"

namespace util {

int itoa(int val, char *buf, int base){
	char *p = buf;
	char *p1, *p2;
	unsigned long uval = val;

	if(base == 10 && val < 0){
		*p++ = '-';
		buf++;
		uval = -val;
	}

	do{
		int remainder = uval % base;
		*p++ = (remainder<10) ? '0'+remainder : 'a'+remainder-10;
	}while(uval /= base);

	*p = '\0';

	p1 = buf;
	p2 = p -1;
	while(p1 < p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return p-buf + (val<0 ? 1 : 0);
}

int vsprintf(char *buf, const char *fmt, va_list args){
	const char *p;
	int i=0;
	long l;

	for(p = fmt; *p!='\0'; p++){
		if(*p != '%'){
			buf[i] = *p;
			i++;
			continue;
		}
		p++;
		switch(*p){
		case 'd':
			l = va_arg(args, int);
			i+= itoa(l, buf+i, 10);
			break;
		case 'x':
			l = va_arg(args, int);
			buf[i++]='0';
			buf[i++]='x';
			i+= itoa(l, buf+i, 16);
			break;
		}
	}
	buf[i]='\0';
	return ++i;
}

int sprintf(char *buf, const char *fmt, ...){
	int i;
	va_list ap;

	va_start(ap, fmt);
	i = vsprintf(buf, fmt, ap);
	va_end(ap);
	return i;
}

} // namespace
