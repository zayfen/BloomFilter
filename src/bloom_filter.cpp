#include <cmath>
#include <stdexcept>


#include "./bloom_filter.hpp"
#include "./bitset.hpp"
#include "./hash_factory.hpp"

class BitSet;
class BloomFilter;
class HashFactory;

BloomFilter::BloomFilter(uint64_t targetCapacity, float falseProbability):
	falseProbability(falseProbability), targetCapacity(targetCapacity), targetSize(0) {

	spBitset = std::make_shared<BitSet>(BloomFilter::getBitsetSize(targetCapacity, falseProbability));
	spHashFactory = std::make_shared<HashFactory>();
}


BloomFilter::BloomFilter(const BloomFilter& rhs) {
	this->falseProbability = rhs.falseProbability;
	this->targetCapacity = rhs.targetCapacity;
	this->targetSize = rhs.targetSize;
	this->spBitset = rhs.spBitset;
}


BloomFilter& BloomFilter::operator = (const BloomFilter& rhs) {
	this->falseProbability = rhs.falseProbability;
	this->targetCapacity = rhs.targetCapacity;
	this->targetSize = rhs.targetSize;
	this->spBitset = rhs.spBitset;
	return *this;
}


void BloomFilter::setHashFactory(std::shared_ptr<HashFactory> &hf) {
	spHashFactory = hf;
}


bool BloomFilter::hit(const HashableItem *item) const {
	if (!spHashFactory.get()) {
		throw std::runtime_error("spHashFactory is invalid, Please call setHashFactory to set correct hash factory");
	}

	std::vector<std::shared_ptr<HashPresent>> presents = spHashFactory.get()->hash(item);
	for (auto& p : presents) {
		// if (p.toUint64() == 0) {
		//	throw std::runtime_error("Please Implement HashPresent::toUint64()");
		// }
		if (!spBitset.get()->test(p.get()->toUint64())) {
			return false;
		}
	}

	return true;
}


uint64_t BloomFilter::addTarget(const HashableItem *item) {
	if (targetSize >= targetCapacity) {
		return targetSize;
	}

	std::vector<std::shared_ptr<HashPresent>> presents = spHashFactory.get()->hash(item);

	for (auto& p: presents) {
		spBitset.get()->set(p.get()->toUint64());
	}

	return targetSize;
}


uint64_t BloomFilter::getBitsetSize(uint64_t targetCapacity, float falseProbability) {
// Math.log(0.001)*10000 / Math.pow(Math.log(2), 2) * -1
	uint64_t size = std::ceil(std::log(falseProbability) * targetCapacity / std::pow(std::log(2), 2) * -1);
	return size;
}

int BloomFilter::getHashFunctionsCount(uint64_t targetCapacity, float falseProbability) {
	uint64_t bitsetSize = BloomFilter::getBitsetSize(targetCapacity, falseProbability);
	return std::ceil(1.0 * bitsetSize / targetCapacity * std::log(2));
}
