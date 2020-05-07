#pragma once
#include <iostream>
#include <new>

/*
	Author: Tucker Dillan Dorjahn
	Version: dev0.8.0
*/

template <typename t_type>
class Node {
private:
	t_type type;
	Node* after;
	Node* before;

public:
	Node(Node* before, t_type key, Node* after) : before(before), type(key), after(after) {}

	Node() {}

	Node(const Node& copy) {
	
		if (copy != nullptr) {

			before = copy.before;
			after = copy.after;
			type = copy.type;

		}
	
	}

	~Node() {

		release();

	}

	Node create(Node* before, t_type type, Node* after) {

		return new Node(before, type, after);

	}

	void release() {

		if (this != nullptr) {

			after = nullptr;
			before = nullptr;
			delete(this);

		}

	}
};