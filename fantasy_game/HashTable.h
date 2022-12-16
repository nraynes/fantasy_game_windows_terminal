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
		int m_size;

		int hash(const std::string& name);

		bool searchBucket(const std::string& name, int& index);

		T* findInBucket(const std::string& name, int& index);

	public:
		void add(const std::string& name, T& item);

		T select(const std::string& name);

		void change(const std::string& name, T& newItem);

		void remove(const std::string& name);

		void forEachItem(void (*cb)(std::string name, T item, int i));
		void forEachItem(void (*cb)(T item, int i));
		void forEachItem(void (*cb)(std::string name, int i));
		void forEachItem(void (*cb)(std::string name, T item));
		void forEachItem(void (*cb)(int i));
		void forEachItem(void (*cb)(T item));
		void forEachItem(void (*cb)(std::string name));
		void forEachItem(void (*cb)());

		int size();
};