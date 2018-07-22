#include <cmath>
#include <exception>
#include <stdexcept>
#include <iostream>

#include "./bitset.hpp"

class BitSet;

BitSet::BitSet(uint64_t size) : size(size) {

	cells = std::ceil(1.0 * size / CellSize);

	std::cout << "cells: " << cells << std::endl;
	std::cout << "CellSize: " << CellSize << std::endl;

	for (uint64_t i = 0; i < cells; i++) {
		bitmap.push_back(CellType(0));
	}
}


void BitSet::set(uint64_t position) {
	if (position >= size) {
		return;
	}

	uint64_t cellIndex = position / CellSize;
	CellType offset = position % CellSize;

	CellType& cell = bitmap[cellIndex];
	CellType mask = CellType(1 << offset);
	cell |= mask;
}


void BitSet::reset(uint64_t position) {
	if (position >= size) {
		return;
	}

	uint64_t cellIndex = position / CellSize;
	CellType offset = position % CellSize;
	std::cout << "cellIndex: " << cellIndex << std::endl;
	std::cout << "offset: " << int(offset) << std::endl;

	CellType& cell = bitmap[cellIndex];
	CellType mask = CellType(0xff) ^ CellType(1 << offset);
	std::cout << "cell: " << int(cell) << " ;mask: " << int(mask) << std::endl;
	cell &= mask;
	std::cout << "After Cell: " << int(cell) << std::endl;
}


void BitSet::reset() {
	for (auto& cell : bitmap) {
		cell = CellType(0);
	}
}


bool BitSet::test(uint64_t position) const {
	if (position >= size) {
		throw std::out_of_range("position is out of range, greater than total bitmap size");
	}

	uint64_t cellIndex = position / CellSize;
	CellType offset = position % CellSize;
	const CellType& cell = bitmap[cellIndex];
	CellType value = cell & CellType(1 << offset);

	if (value == 0) {
		return false;
	}

	return true;
}
