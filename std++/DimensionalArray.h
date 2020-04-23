#pragma once

/* DIMENSIONALARRAY.H
 * @author: Tucker D. Dorjahn
 * @version: dev 0.1
 */

#include <iostream>
#include <string>
#include <exception>
#include <initializer_list>

template <typename t_type, int N>
class DimensionalArray {
private:
	unsigned int dimensions;
	unsigned int size;
	t_type* mult_array;

	void init_list(std::initializer_list<t_type> list) {
		for (auto element : list)
			std::cout << element << '\n';
	}

public:
	DimensionalArray(unsigned int dimensions) : dimensions(dimensions), size(N) {
		mult_array = new t_type[dimensions * size];
	}

	DimensionalArray(const DimensionalArray<t_type, N>& copy) {
		dimensions = copy.dimensions;
		size = copy.size;

		memccpy(mult_array, copy.mult_array, dimensions * size);
	}

	~DimensionalArray() {
		delete[] mult_array;
	}

	//This is intended used for 2 dimensional arrays and above
	template<typename ... Args>
	t_type& at(t_type type, Args&&... args) {
		
	}

	t_type& operator[](unsigned int index) throw (std::out_of_range) {
		try {
			return mult_array[index];
		}
		catch (std::out_of_range e) {
			std::cerr << "ERROR: " << e.what() << '\n';
		}
			
	}

	friend std::ostream& operator<<(std::ostream& os, const DimensionalArray<t_type, N>& obj) {
		os << obj.dimensions;

		return os;
	}

	

};