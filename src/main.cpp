#include <iostream>
#include <memory>

#include "./bitset.hpp"
#include "./bloom_filter.hpp"
#include "./hash_factory.hpp"

class BitSet;
class HashableItem;
class HashPresent;
class HashBase;


class String: public HashableItem, public std::string {
public:
	String(const char* chars): std::string(chars), s(chars) {

	}

	virtual const std::string serialize() const override {
		return s;
	}
private:
	std::string s;
};



class HashOne: public HashBase {
public:
	virtual std::shared_ptr<HashPresent> hash(const HashableItem* item) override {
		return std::make_shared<HashPresent>(item->serialize());
	}
};

int main(int argc, char* argv[]) {

	std::cout << "Hello World" << std::endl;

	BitSet bs(100);
	bs.set(10);
	std::cout << bs.test(10) << std::endl;
	bs.reset(10);
	std::cout << bs.test(10) << std::endl;


	HashOne hone;
	std::shared_ptr<HashPresent> spHashPresent = hone.hash(new String("hello world"));
	std::cout << spHashPresent.get()->toString() << std::endl;
	std::cout << spHashPresent.get()->toInt() << std::endl;
	std::cout << spHashPresent.get()->toUint64() << std::endl;

	BloomFilter bf(10000, 0.01);
	std::shared_ptr<HashFactory> spHf(new HashFactory());
	spHf.get()->pushHash(std::make_shared<HashOne>());
	bf.setHashFactory(spHf);
	std::cout << "add target 'zayafa'" << std::endl;
	bf.addTarget(new String("zayafa"));

	std::cout << "zayafa existed? " <<  bf.hit(new String("zayafa")) << std::endl;
	std::cout << "zayafa2 existed? " <<  bf.hit(new String("zayafa2")) << std::endl;
	return 0;
}
