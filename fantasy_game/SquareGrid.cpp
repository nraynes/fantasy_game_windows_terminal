#include <memory>
#include <string>
#include "SquareGrid.h"

template<class T>
SquareGridNode<T>::SquareGridNode(const std::string& name, const T& data, HashTable<std::shared_ptr<SquareGridNode<T>>>* grid) : m_name(name), m_data(data), m_grid(grid), m_left(nullptr), m_right(nullptr), m_top(nullptr), m_bottom(nullptr) {}

template<class T>
T& SquareGridNode<T>::data() {
	return m_data;
}

template<class T>
void SquareGridNode<T>::setLeft(const std::string& name, const T& data) {
	std::shared_ptr<SquareGridNode<T>>newNode(new SquareGridNode(name, data));
	m_grid.add(name, newNode);
	m_left = newNode;
}

template<class T>
void SquareGridNode<T>::removeLeft() {
	m_left = nullptr;
}

template<class T>
std::shared_ptr<SquareGridNode<T>> SquareGridNode<T>::left() {
	return m_left;
}

template<class T>
void SquareGridNode<T>::setRight(const std::string& name, const T& data) {
	std::shared_ptr<SquareGridNode<T>>newNode(new SquareGridNode(name, data));
	m_grid.add(name, newNode);
	m_right = newNode;
}

template<class T>
void SquareGridNode<T>::removeRight() {
	m_right = nullptr;
}

template<class T>
std::shared_ptr<SquareGridNode<T>> SquareGridNode<T>::right() {
	return m_right;
}

template<class T>
void SquareGridNode<T>::setTop(const std::string& name, const T& data) {
	std::shared_ptr<SquareGridNode<T>>newNode(new SquareGridNode(name, data));
	m_grid.add(name, newNode);
	m_top = newNode;
}

template<class T>
void SquareGridNode<T>::removeTop() {
	m_top = nullptr;
}

template<class T>
std::shared_ptr<SquareGridNode<T>> SquareGridNode<T>::top() {
	return m_top;
}

template<class T>
void SquareGridNode<T>::setBottom(const std::string& name, const T& data) {
	std::shared_ptr<SquareGridNode<T>>newNode(new SquareGridNode(name, data));
	m_grid.add(name, newNode);
	m_bottom = newNode;
}

template<class T>
void SquareGridNode<T>::removeBottom () {
	m_bottom = nullptr;
}

template<class T>
std::shared_ptr<SquareGridNode<T>> SquareGridNode<T>::bottom() {
	return m_bottom;
}

template<class T>
SquareGrid<T>::SquareGrid(const std::string& name, const T& data) {
	std::shared_ptr<SquareGridNode<T>>newNode(new SquareGridNode<T>(name, data, &nodes));
	nodes.add(name, newNode);
}

template<class T>
std::shared_ptr<SquareGridNode<T>> SquareGrid<T>::node(const std::string& name) {
	return nodes.select(name);
}

template<class T>
void SquareGrid<T>::removeNode(const std::string& name) {
	std::shared_ptr<SquareGridNode<T>>selected(nodes.select(name));
	if (selected.right()) {
		selected.right()->removeLeft();
	}
	if (selected.left()) {
		selected.left()->removeRight();
	}
	if (selected.top()) {
		selected.top()->removeBottom();
	}
	if (selected.bottom()) {
		selected.bottom()->removeTop();
	}
	nodes.remove(name);
}