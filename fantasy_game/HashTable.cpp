#include "HashTable.h"

template<class T, int tableSize>
int HashTable<T, tableSize>::hash(const std::string& name) {
	int hash = 0;
	for (int i = 0; i < name.size(); i++) {
		hash += int(name[i]);
	}
	return hash % tableSize;
}

template<class T, int tableSize>
bool HashTable<T, tableSize>::searchBucket(const std::string& name, int& index) {
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			return true;
		}
	}
	return false;
}

template<class T, int tableSize>
T* HashTable<T, tableSize>::findInBucket(const std::string& name, int& index) {
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			T* selectedItem = &table[index][i].item;
			return selectedItem;
		}
	}
	return nullptr;
}

template<class T, int tableSize>
void HashTable<T, tableSize>::add(const std::string& name, T& item) {
	Unit<T> unit;
	unit.name = name;
	unit.item = item;
	int index = hash(name);
	if (!searchBucket(name, index)) {
		table[index].push_back(unit);
		m_size++;
	}
}

template<class T, int tableSize>
T HashTable<T, tableSize>::select(const std::string& name) {
	int index = hash(name);
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			return table[index][i].item;
		}
	}
	return T();
}

template<class T, int tableSize>
void HashTable<T, tableSize>::change(const std::string& name, T& newItem) {
	int index = hash(name);
	T* item = findInBucket(name, index);
	if (item) {
		*item = newItem;
	}
}

template<class T, int tableSize>
void HashTable<T, tableSize>::remove(const std::string& name) {
	int index = hash(name);
	for (int i = 0; i < table[index].size(); i++) {
		if (table[index][i].name == name) {
			table[index].erase(table[index].begin() + i);
			m_size--;
			return;
		}
	}
}

template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)(std::string name, T item, int i)) {
	int count = 0;
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb(table[i][j].name, table[i][j].item, count);
			count++;
		}
	}
}
template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)(T item, int i)) {
	int count = 0;
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb(table[i][j].item, count);
			count++;
		}
	}
}
template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)(std::string name, int i)) {
	int count = 0;
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb(table[i][j].name, count);
			count++;
		}
	}
}
template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)(std::string name, T item)) {
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb(table[i][j].name, table[i][j].item);
		}
	}
}
template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)(int i)) {
	int count = 0;
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb(count);
			count++;
		}
	}
}
template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)(T item)) {
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb(table[i][j].item);
		}
	}
}
template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)(std::string name)) {
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb(table[i][j].name);
		}
	}
}
template<class T, int tableSize>
void HashTable<T, tableSize>::forEachItem(void (*cb)()) {
	int count = 0;
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cb();
			count++;
		}
	}
}

template<class T, int tableSize>
int HashTable<T, tableSize>::size() {
	return m_size;
}