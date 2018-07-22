#ifndef __BLOOM_FILTER_HPP__
#define __BLOOM_FILTER_HPP__

#include <cstdint>
#include <memory>

class BitSet;
class HashFactory;
class HashableItem;

class BloomFilter {

public:
	BloomFilter() = delete;

	BloomFilter( uint64_t targetCapacity, float falseProbability);

	BloomFilter(const BloomFilter& rhs);

	static uint64_t getBitsetSize(uint64_t targetSize, float falseProbability);

	static int getHashFunctionsCount(uint64_t targetSize, float falseProbability);


	void setHashFactory(std::shared_ptr<HashFactory>& hf);

	BloomFilter& operator = (const BloomFilter& rhs);

	bool hit(const HashableItem* item) const;

	uint64_t addTarget(const HashableItem* item);

private:
	float falseProbability;
	uint64_t targetCapacity;
	uint64_t targetSize;
	std::shared_ptr<BitSet> spBitset;
	std::shared_ptr<HashFactory> spHashFactory;
};

#endif // end of __BLOOM_FILTER_HPP__
