#pragma once

/*
	Author: Tucker Dillan Dorjahn
	Version: 0.2.0

*/


#include <iostream>
#include <exception>
#include <unordered_map>


namespace cString {

	enum error_t {
		OUT_OF_RANGE = 0,
		NULL_POINTER = 1,
		MEM_LEAK = 2
	};

	class String {

	private:
		char* m_buffer;
		unsigned int m_size;

		void terminate() { //adds terminator character, got sick of writing this one liner a lot, so I made it into a function.

			m_buffer[m_size] = 0;

		}

	public:
		String(const char* buffer) {

			m_size = strlen(buffer);
			m_buffer = new char[m_size + 1];

			memcpy(m_buffer, buffer, m_size);
			terminate();

		}

		~String() {

			delete[] m_buffer;

		}

		String(const String& copy) {

			m_size = copy.m_size;
			m_buffer = new char[m_size + 1];
			memcpy(m_buffer, copy.m_buffer, m_size);
			terminate();

			std::cout << "Copied" << std::endl;

		}

		char at(unsigned int index) throw (std::out_of_range) {

			try {
			
				if (index < 0 || index >= m_size) {

					throw std::out_of_range("index can only be between 0 and ");

				}
					
			}
			catch (const std::out_of_range& e) {
			
				std::cerr << "ERROR: " << e.what() << m_size << '\n';
			
			}
			
		}

		char front() {

			if (m_size != 0)
				return at(0);
		}

		char back() {

			if (m_size != 0)
				return at(strlen(m_buffer + 1));

		}

		void append(const char* string) {

			m_size += strlen(string);

			operator+(string);

		}

		void prepend(const char* string) {

			m_size += strlen(string);
			char* t_buffer = m_buffer;
			m_buffer = new char[m_size + 1];

			m_buffer = (char*)string;
			operator+(t_buffer);

		}

		/*Insert defined behavior
			String will resize itself to accommodate for the new character(s).
			Everything on the right of index will shift to the right, prepending the string argument starting at index.
		*/

		void insert(const char* string, unsigned int index) throw (std::out_of_range) {


			char* r_str = this->substr(index, strlen(string));

			/* r_str = string[index] + string[index+1] + ... + string[n] */

			if (index == 0) {
			
				prepend(string);
			
			}
				
			else if (index == m_size) {

				append(string);

			}
				
			else {

				m_size += strlen(string) + 1;


				/*
					Adds the argument string into m_buffer.
				*/

				for (int i = 0; i < strlen(string) - 1; i++) {

					m_buffer[i + index] = string[i];

				}

				/*
					Reintroduces r_str to the right of the inserted argument string.
				*/

				for (int i = m_size - (strlen(r_str) + 1), j = 0; i < m_size; i++, j++) {
					
					m_buffer[i] = r_str[j];

				}

			}

			terminate();

			delete[] r_str;

		}

		char*& substr(unsigned int index, unsigned int len) throw (std::out_of_range) {

			try {

				this->at(index);

			}
			catch (std::out_of_range e) { }

			char* r_str = new char[len + 1];
			r_str[len] = 0;


			std::copy(m_buffer + index, m_buffer + index + len, r_str);

			return r_str;


			/*
				NOTE:
				r_str does NOT get freed in the heap within this function.
			*/

		}

		bool is_empty() {

			return m_size > 0;

		}

		String& operator+(const String& rhs) {

			m_size = m_size + rhs.m_size;
			char* t_buffer = m_buffer;
			m_buffer = new char[m_size + 1];

			strcpy(m_buffer, t_buffer);
			strcat(m_buffer, rhs.m_buffer);
			terminate();

			return *this;

		}

		String& operator+=(const String& rhs) {

			return operator+(rhs);

		}

		bool operator==(const String& string) {

			return *this == string;

		}

		bool operator==(unsigned int number) {

			return number == 0 && m_size == 0;

		}

		char& operator[](unsigned int index) throw (int) {

			char res;

			try {

				if (index > -1 || index < m_size)
					res = m_buffer[index];
				else
					throw OUT_OF_RANGE;

				if (m_buffer[index] == NULL)
					throw NULL_POINTER;

				if (m_buffer == nullptr)
					throw MEM_LEAK;

			}
			catch (int e) {
				std::cerr << "[INVALID INDEX]: ERROR " << e << " ";
				res = (char&)e;

			}

			return res;
		}

		String& operator=(const String& string) {

			return *this = String(string);

		}

		friend std::ostream& operator<<(std::ostream& stream, const String& string);

		template<typename ... Args>
		friend void printf(const String& string, Args&& ... args);
		friend void print(const String& string);


	};

	std::ostream& operator<<(std::ostream& stream, const String& string) {

		stream << string.m_buffer;
		return stream;

	}

	void print(const String& string) {

		std::cout << string;

	}


	/*TODO: implement insert() into printf() */
	template <typename ... Args>
	void printf(const String& string, Args&& ... args) {

		std::unordered_map<int, char> cmap; //character map
		std::unordered_map<int, char> fmap; //format specificer map with specifier location within a string

		for (int i = 0; i < string.m_size; i++) {

			cmap[i] = string.m_buffer[i];

		}

		for (int i = 0; i < cmap.size(); i++) {

			if (cmap[i] == '%')
				fmap[i + 1] = cmap[i + 1];

		}

		
		
	}

}