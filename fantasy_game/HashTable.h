#pragma once
#include <string>
#include <vector>

template<class T>
struct Unit {
	std::string name;
	T item;
};

template<class T, int tableSize = 10>
class HashTable {
	private:
		std::vector<Unit<T>> table[tableSize];

		int hash(std::string& name);

		bool searchBucket(std::string& name, int& index);

		T* findInBucket(std::string& name, int& index);

	public:
		void add(std::string& name, T& item);

		T select(std::string& name);

		void change(std::string& name, T& newItem);

		void remove(std::string& name);
};