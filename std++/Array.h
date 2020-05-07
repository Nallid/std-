#pragma once
#include <iostream>
#include "Node.h"

template <typename m_type, unsigned int N>
class Array {
private:
	unsigned int m_size;
	Node<m_type> root;

public:
	Array<m_type, N>() : m_size(N) {}


};