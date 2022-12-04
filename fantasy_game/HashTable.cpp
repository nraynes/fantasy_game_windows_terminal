#include <vector>
#include <string>

template<class T>
struct Unit {
	std::string name;
	T item;
};

template<class T, int tableSize = 10 >
class HashTable {
	private:
		std::vector<Unit<T>> table[tableSize];

		int hash(std::string& name) {
			int hash = 0;
			for (int i = 0; i < name.size(); i++) {
				hash += int(name[i]);
			}
			return hash % tableSize;
		}

		bool searchBucket(std::string& name, int& index) {
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index][i].name == name) {
					return true;
				}
			}
			return false;
		}

		T* findInBucket(std::string& name, int& index) {
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index][i].name == name) {
					T* selectedItem = &table[index][i].item;
					return selectedItem;
				}
			}
			return nullptr;
		}

	public:
		void add(std::string& name, T& item) {
			Unit<T> unit;
			unit.name = name;
			unit.item = item;
			int index = hash(name);
			if (!searchBucket(name, index)) {
				table[index].push_back(unit);
			}
		}

		T select(std::string& name) {
			int index = hash(name);
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index][i].name == name) {
					return table[index][i].item;
				}
			}
			return T();
		}

		void change(std::string& name, T& newItem) {
			int index = hash(name);
			T* item = findInBucket(name, index);
			if (item) {
				*item = newItem;
			}
		}

		void remove(std::string& name) {
			int index = hash(name);
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index][i].name == name) {
					table[index].erase(table[index].begin() + i);
				}
			}
		}
};