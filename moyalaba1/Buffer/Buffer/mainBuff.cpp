#pragma once
#include <iostream>

#include "Buff.h"

using namespace std;

//Construction
CircularBuffer::CircularBuffer() {
	buffer = nullptr;
	first = 0;
	length = count = 0;
}

//Contstruction
CircularBuffer::CircularBuffer(const CircularBuffer & cb) {
	*this = (cb);
}

//Destruction
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

//Creating bufffer with given opacity & filling it all the way with the given value
CircularBuffer::CircularBuffer(int capacity, const value_type & elem) : CircularBuffer(capacity) {
	//count = capacity;
	for (int i = 0; i < capacity; i++) {
		buffer[i] = elem;
	 }
}

//Returns the linear index from the residue ring(кольцо вычетов)
int CircularBuffer::linear_index(int i) const {
	return (first + i + length) % length;
}

//Index access. (Not checking the index)
value_type & CircularBuffer::operator [](int i) {
	return buffer[linear_index(i)];
}

//Index access. (Not checking the index)
const value_type & CircularBuffer::operator[](int i) const {
	return buffer[linear_index(i)];
}

//Index access. Checking if the index is correct or not
value_type & CircularBuffer::at(int i) {
	if (i < length || i >= count)
		throw std::invalid_argument("invalid index");
	return operator[](i);
}
//Index access. Checking if the index is correct or not
const value_type & CircularBuffer::at(int i) const {
	if (i < length || i >= count)
		throw std::invalid_argument("invalid index");
	return operator[](i);
}

//Link to the first element
value_type & CircularBuffer::front() {
	return at(first);
}

//Link to the back element
value_type & CircularBuffer::back() {
	return at(count);
}

//Link to the first element
const value_type & CircularBuffer::front() const {
	return at(first);
}

//Link to the back element
const value_type & CircularBuffer::back() const {
	return at(count);
}

//Making buffer go in line
value_type* CircularBuffer::linearize() {
	value_type* newarray = new value_type[length];
	for (int i = 0; i < length; ++i) {
		newarray[i] = at(i);
	}
	delete[] buffer;
	buffer = newarray;
	first = 0;
	return buffer;
}

//Checking if the buffer is linearized
bool CircularBuffer::is_linearized() const {
	return first == 0;
}

//Buffer Rotation
void CircularBuffer::rotate(int new_begin) {
	first = new_begin;
	buffer = linearize();
}

//Number of elements kept in the buffer
int CircularBuffer::size() const {
	return count;
}

//Buffer capacity
int CircularBuffer::capacity() const {
	return length;
}

//The number of an empty cells
int CircularBuffer::reserve() const {
	return capacity() - size();
}

bool CircularBuffer::empty() const {
	return size() == 0;
}

//True if size == count
bool CircularBuffer::full() const {
	return size() == capacity();
}


//Pushes element in the end of the buffer
void CircularBuffer::push_back(const value_type & v) {
	if (full()) {
		buffer[first] = v;
		first = linear_index(1);
	}
	else {
		buffer[linear_index(count)] = v;
		++count;
	}
}

//Pushes element in the beginning of the buffer
void CircularBuffer::push_front(const value_type & v) {
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

//New capacity
void CircularBuffer::set_capacity(int new_capacity) {
	//Вызываем деструктор и вызываем конструктор?
	value_type* oldbuff = buffer;
	buffer = new value_type[new_capacity];
	if (new_capacity > count) {
		for (int i = 0; i < count; ++i) {
			buffer[i] =oldbuff[i];
		}
	}
	else {
		for (int i = 0; i < new_capacity; ++i) {
			buffer[i] = oldbuff[i];
		}
		count = new_capacity;
	}
}

//Swaping items between Buffers
void CircularBuffer::swap(CircularBuffer & cb) {
	value_type* move = buffer;
	int move_length = length;
	int move_count = count;
	int move_first = first;

	buffer = cb.buffer;
	length = cb.length;
	count = cb.count;
	first = cb.first;

	cb.buffer = move;
	cb.length = move_length;
	cb.count = move_count;
	cb.first = move_first;
}

//Resiz
void CircularBuffer::resize(int new_size, const value_type & item) {
	if (length > new_size) {
		set_capacity(new_size);
	}
	else {
		int to_fill = new_size - size();
		set_capacity(new_size);
		for (int i = 1; i <= to_fill; ++i) {
			at(-i) = item;
		}
	}

}

CircularBuffer & CircularBuffer::operator=(const CircularBuffer & cb) {
	buffer = new value_type[cb.length];
	first = cb.first;
	count = cb.count;
	length = cb.length;
	for (int i = 0; i < count; ++i) {
		buffer[i] = cb.buffer[i];
	}
	return *this;
}

void CircularBuffer::pop_back() {
	count--;
}

void CircularBuffer::pop_front() {
	first = linear_index(1);
}


//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
void CircularBuffer::insert(int pos, const value_type & item) {
	at(pos) = item;
}

//Удаляет элементы из буфера в интервале [first, last).
void CircularBuffer::erase(int first, int last) {
	int to_move = last;
	for (int i = first; i < last; ++i) {
		at(i).~value_type();
	}
	for (int i = 0; i < (count - last); ++i) {
		at(first + i) = at(last + i);
	}
	count = count - (last - first);
}

//Очищает буфер.
void CircularBuffer::clear() {
	for (int i = 0; i < size(); ++i) {
		(*this)[i].~value_type();
	}
	count = 0;
}


bool operator==(const CircularBuffer & a, const CircularBuffer & b) {
	if (&a == &b)
		return true;
	if (a.size() != b.size())
		return false;
	
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

bool operator!=(const CircularBuffer & a, const CircularBuffer & b) {
	return !(a == b);
}