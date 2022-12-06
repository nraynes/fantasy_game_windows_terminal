#include "HashTable.h"

template<class T, int tableSize>
int HashTable<T, tableSize>::hash(std::string& name) {
	int hash = 0;
	for (int i = 0; i < name.size(); i++) {
		hash += int(name[i]);
	}
	return hash % tableSize;
}

template<class T, int tableSize>
bool HashTable<T, tableSize>::searchBucket(std::string& name, int& index) {
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			return true;
		}
	}
	return false;
}

template<class T, int tableSize>
T* HashTable<T, tableSize>::findInBucket(std::string& name, int& index) {
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			T* selectedItem = &table[index][i].item;
			return selectedItem;
		}
	}
	return nullptr;
}

template<class T, int tableSize>
void HashTable<T, tableSize>::add(std::string& name, T& item) {
	Unit<T> unit;
	unit.name = name;
	unit.item = item;
	int index = hash(name);
	if (!searchBucket(name, index)) {
		table[index].push_back(unit);
	}
}

template<class T, int tableSize>
T HashTable<T, tableSize>::select(std::string& name) {
	int index = hash(name);
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			return table[index][i].item;
		}
	}
	return T();
}

template<class T, int tableSize>
void HashTable<T, tableSize>::change(std::string& name, T& newItem) {
	int index = hash(name);
	T* item = findInBucket(name, index);
	if (item) {
		*item = newItem;
	}
}

template<class T, int tableSize>
void HashTable<T, tableSize>::remove(std::string& name) {
	int index = hash(name);
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			table[index].erase(table[index].begin() + i);
		}
	}
}