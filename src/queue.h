#ifndef QUEUE_H_
#define QUEUE_H_

#include "common.h"

template<typename T, size_t SIZE>
class queue {
public:
	queue() : read(0), write(0) {free=SIZE;}

	size_t size() const {
		return SIZE-free;
	}
	bool empty() const {
		return size() == 0;
	}

	void push(const T &val){
		if(write == SIZE)
			write = 0;
		buf[write] = val;
		write++;
		free--;
	}

	const T& front() const {
		return buf[read];
	}
	const T& pop(){
		auto& data = buf[read];
		read++;
		if(read == SIZE)
			read = 0;
		free++;
		return data;
	}
private:
	T buf[SIZE];
	size_t read, write;
	size_t free;
};

#endif
