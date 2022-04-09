# NOTE: Do not change.

# Default target.
all: hash_driver

# Makes extendible_hash.o
extendible_hash: extendible_hash.cpp
	g++ -c extendible_hash.cpp

# Makes the main executable.
hash_driver: extendible_hash
	g++ -o hash_driver hash_driver.cpp extendible_hash.o
