#pragma once
#include <vector>
#include <memory>
#include <string>
#include "HashTable.h"

template<class T>
class SquareGridNode {
	private:
		std::string m_name;
		T m_data;
		std::shared_ptr<SquareGridNode<T>> m_left;
		std::shared_ptr<SquareGridNode<T>> m_right;
		std::shared_ptr<SquareGridNode<T>> m_top;
		std::shared_ptr<SquareGridNode<T>> m_bottom;
		HashTable<std::shared_ptr<SquareGridNode<T>>>* m_grid;

	public:
		SquareGridNode(const std::string& name, const T& data, HashTable<std::shared_ptr<SquareGridNode<T>>>* grid);

		T& data();

		void setLeft(const std::string& name, const T& data);

		void removeLeft();

		std::shared_ptr<SquareGridNode<T>> left();

		void setRight(const std::string& name, const T& data);

		void removeRight();

		std::shared_ptr<SquareGridNode<T>> right();

		void setTop(const std::string& name, const T& data);

		void removeTop();

		std::shared_ptr<SquareGridNode<T>> top();

		void setBottom(const std::string& name, const T& data);

		void removeBottom();

		std::shared_ptr<SquareGridNode<T>> bottom();
};

template<class T>
class SquareGrid {
	private:
		HashTable<std::shared_ptr<SquareGridNode<T>>> nodes;

	public:
		SquareGrid(const std::string& name, const T& data);

		std::shared_ptr<SquareGridNode<T>> node(const std::string& name);

		void removeNode(const std::string& name);
};