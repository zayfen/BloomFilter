#ifndef __BITSET_HPP__
#define __BITSET_HPP__

#include <cstdint>
#include <vector>

class BitSet {
	using CellType = uint8_t;

public:
	BitSet(uint64_t size);

	void set(uint64_t position);

	void reset(uint64_t position);

	void reset();

	bool test(uint64_t position) const;

private:

	uint64_t size;
	std::vector<CellType> bitmap;
	uint64_t cells;
	const int CellSize = sizeof (CellType) * 8; // bits
};

#endif // endif here
