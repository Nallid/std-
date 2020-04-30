#pragma once

/*
	Author: Tucker Dillan Dorjahn
	Version: 0.4.0
*/

#include <iostream>
#include <chrono>

unsigned static int timer_id_count = 0;
#define chrono std::chrono

class Timer {
private:
	
public:
	unsigned int function_id = 0;

	explicit Timer() {
		timer_id_count++;
		function_id+= timer_id_count;
	}

	/* This will time any function if provided a pointer of the function and its arguments if any.
	   Ex:

	   Funciton: int add(int x, int y) { return x + y; }
	   Called: time_function (add, 1, 2);

	   If no arguments are taken, only the function pointer is to be put as an argument for time_function()

	   Cannot take functions that include members. Looking to fix this.
	*/

	template <typename T, typename ... Args>
	auto time_function(T function, Args&& ... args) {
		auto start = chrono::high_resolution_clock::now();

		function(std::forward<Args>(args) ...);

		auto stop = chrono::high_resolution_clock::now();


		return chrono::duration_cast<chrono::nanoseconds>(stop - start);
	}

};

template <typename T, typename ... Args>
auto time_function(T function, Args&& ... args) {
	auto start = chrono::high_resolution_clock::now();

	function(std::forward<Args>(args) ...);

	auto stop = chrono::high_resolution_clock::now();


	return chrono::duration_cast<chrono::nanoseconds>(stop - start);
}


auto start_timer() {
	return chrono::high_resolution_clock::now();

}

void stop_timer(chrono::steady_clock::time_point start) {
	auto stop = chrono::high_resolution_clock::now();

	std::cout << (chrono::duration_cast<chrono::nanoseconds>(stop - start)).count();
}