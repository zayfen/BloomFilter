#include "./hash_factory.hpp"



HashFactory::HashFactory() {
	hashs.clear();
}


std::vector<std::shared_ptr<HashPresent>> HashFactory::hash(const HashableItem *item) {
	std::vector<std::shared_ptr<HashPresent>> presents;
	presents.clear();

	if (item == nullptr) {
		return presents;
	}

	for (auto& hash : hashs) {
		presents.push_back(hash.get()->hash(item));
	}

	return presents;
}



void HashFactory::pushHash(std::shared_ptr<HashBase> hb) {
	hashs.push_back(hb);
}



void HashFactory::removeHash(HashBase *ptr) {
	for (size_t i = 0; i < hashs.size(); i++) {
		if (hashs[i].get() == ptr) {
			hashs.erase(hashs.begin() + i);
		}
	}
}
