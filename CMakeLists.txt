cmake_minimum_required(VERSION 3.1.0)

project(BloomFilter CXX)

set(SRC
	./src/bitset.cpp
	./src/bloom_filter.cpp
	./src/hash_factory.cpp
	./src/main.cpp)

message("Source Files Are ${SRC}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -g")


add_executable(bloomfilter ${SRC})
set_property(TARGET bloomfilter PROPERTY CXX_STANDARD 14)
