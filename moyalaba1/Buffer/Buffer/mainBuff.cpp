#pragma once
#include <iostream>

#include "Buff.h"

using namespace std;

CircularBuffer::CircularBuffer() {
	buffer = nullptr;
	first = 0;
	length = count = 0;
}

CircularBuffer::CircularBuffer(const CircularBuffer & cb) {
	//Dont forget to make func to copy arrays 
	//buffer_head = cb.buffer_head;
	//buffer_tail = cb.buffer_tail;
	//busy = cb.busy;
	//length = cb.length;
	//isempty = cb.isempty;
}

CircularBuffer::~CircularBuffer() {
	delete[] buffer;
}

//Creating buffer with given opacity
CircularBuffer::CircularBuffer(int capacity) {
	buffer = new value_type[capacity];
	first = 0;
	count = 0;
	length = capacity;
}

//Creating bufffer with given opacity & filling it all the way with given value
CircularBuffer::CircularBuffer(int capacity, const value_type & elem) : CircularBuffer(capacity) {
	for (int i = 0; i < capacity; i++) {
		buffer[i] = elem;
	 }
}

int CircularBuffer::linear_index(int i) const {
	return (first + i + length) % length;
}

value_type & CircularBuffer::operator [](int i) {
	return buffer[linear_index(i)];
}

const value_type & CircularBuffer::operator[](int i) const {
	return buffer[linear_index(i)];
}

bool CircularBuffer::full() const {
	return count == length;
}

void CircularBuffer::push_back(const value_type& v) {
	if (full()) {
		first = linear_index(1);
		buffer[first] = v;
	}
	else {
		buffer[linear_index(count)] = v;
		++count;
	}
}

void CircularBuffer::push_back(const value_type& v) {
	if (full()) {
		first = linear_index(-1);
		buffer[first] = v;
	}
	else {
		first = linear_index(-1);
		buffer[first] = v;
		count++;
	}
}

value_type & CircularBuffer:: operator [](int i) {
	return buffer[linear_index(i)];

}
const value_type & CircularBuffer::operator [](int i) const {
	return buffer[linear_index(i)];
}

value_type & CircularBuffer::at(int i) {
	if (i < 0 || i >= count)
		throw std::invalid_argument("invalid index");
	return operator[](i);
}

const value_type & CircularBuffer::at(int i) const {
	if (i < 0 || i >= count)
		throw std::invalid_argument("invalid index");
	return operator[](i);
}

value_type* CircularBuffer::linearize() {
	value_type* newarray = new value_type[length];
	for (int i = 0; i < length; ++i) {
		newarray[i] = at(i);
	}
	delete[] buffer;
	buffer = newarray;
	first = 0;
}

bool CircularBuffer::is_linearized() const {
	return first == 0;
}

value_type & CircularBuffer::front() {
	return at(first);
}
value_type & back();  //—сылка на последний элемент.
