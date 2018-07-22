#ifndef __HASH_FACTORY_HPP__
#define __HASH_FACTORY_HPP__

#include <string>
#include <vector>
#include <memory>

////// define interfaces /////////
class HashableItem {
public:
	HashableItem() = default;
	virtual const std::string serialize() const = 0;
};


class HashPresent {
public:
	HashPresent() = delete;
	HashPresent(const std::string str): hashStr(str) {

	}

	virtual const std::string toString() {
		return hashStr;
	}

	virtual int toInt() {
		return hashStr.size();
	}

	virtual uint64_t toUint64() {
		return hashStr.size();
	}

private:
	const std::string hashStr;
};


class HashBase {
public:
	virtual std::shared_ptr<HashPresent> hash(const HashableItem* item) = 0;
};


class HashFactory {
public:
	HashFactory();

	std::vector<std::shared_ptr<HashPresent>> hash(const HashableItem* item);

	void pushHash(std::shared_ptr<HashBase> hb);
	void removeHash(HashBase* ptr);

private:

	std::vector<std::shared_ptr<HashBase>> hashs;
};

#endif
