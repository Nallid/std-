#pragma once

/*
	Author: Tucker Dillan Dorjahn
	Version: 0.3.0

*/


#include <iostream>
#include <exception>

struct format_flags {

	/* specifiers */
	const char s_decimal = 'd';
	const char s_octal = 'o';
	const char s_hexa = 'h';
	const char s_floating_lower = 'f';
	const char s_floating_upper = 'F';
	const char s_exponent_lower = 'e';
	const char s_exponent_upper = 'E';
	const char s_character = 'c';
	const char s_string = 's';
	const char s_pointer = 'p';
	const char s_nothing = 'n';

	/* flags */
	const char f_dash = '-';
	const char f_plus = '+';
	const char f_space = ' ';
	const char f_pound = '#';
	const char f_terminate = 0;

	/* precision */
	const char p_pre = '.';

	/* length specificers */
	const char short_int = 'qq';
	const char long_int = 'l';
	const char long_long_int = 'll';

	/* printf("Integer with precision of 2: %d.2\n", 123);
	stream: Integer with precision of 2: 12

	*/
};


namespace cString {

	enum error_t {
		OUT_OF_RANGE = 0,
		NULL_POINTER = 1,
		MEM_LEAK = 2
	};

	class String {

	private:
		char* m_buffer;
		size_t m_size;

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

				return m_buffer[index];
					
			}
			catch (const std::out_of_range& e) {
			
				std::cerr << "ERROR: " << e.what() << m_size << '\n';
			
			}

			
		}

		char front() {

			if (m_size != 0) {
			
				return at(0);
			
			}
				
		}

		char back() {

			if (m_size != 0) {
			
				return at(strlen(m_buffer + 1));
			
			}
				

		}

		void append(const char* string) {

			operator+(string);

		}

		void prepend(const char* string) {

			m_size = strlen(string);
			char* t_buffer = m_buffer;
			std::cout << strlen(t_buffer) << std::endl;

			std::cout << strlen(m_buffer) << std::endl;

			m_buffer = (char*)string;
			operator+(t_buffer);

		}

		/*Insert defined behavior
			String will resize itself to accommodate for the new character(s).
			Everything on the right of index will shift to the right, prepending the string argument starting at index.
		*/

		void insert(const char* string, unsigned int index) throw (std::out_of_range) {


			char* r_str;

			/* r_str = string[index] + string[index+1] + ... + string[n] */

			if (index == 0) {
			
				prepend(string);
			
			}
				
			else if (index == m_size) {

				append(string);

			}
				
			else {

				r_str = substr(index, strlen(string));

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

				delete[] r_str;

				/*
					New string, new terminate character.
				*/

				terminate();

			}

		}

		char* substr(unsigned int index, size_t len) throw (std::out_of_range) {

			try {

				this->at(index);

			}
			catch (std::out_of_range e) { /* using at() catch statement */ }

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

		void copy(const String& copy) {

			*this = String(copy);

		}

		size_t capacity() {

			if (m_size < 15)

				return 15;

			else

				return m_size;

		}

		size_t find(const char ch) {

			for (int i = 0; i < m_size; i++) {

				if (m_buffer[i] == ch)

					return i;

			}

			return -1;

		}

		size_t find(const char* ptr) throw (std::runtime_error){

			try {

				if (ptr == nullptr) {

					throw std::runtime_error("ptr must contain a value");

				}

				for (int i = 0; i < m_size; i++) {

					if (*ptr == m_buffer[i])

						return i;

				}

			}

			catch (std::runtime_error e) {

				std::cout << e.what() << '\n';

			}

			/* not found */
			return -1;

		}


		
		int compare(const String& string) {

			int result = 0;

			for (int i = 0; i < m_size; i++) {

				if (string.m_buffer[i] != m_buffer[i])
					result += m_buffer[i];
			}

			return result;

		}

		String& to_binary(const String& string) {

			

		}

		

		String& const operator+(const String& rhs) {

			m_size += rhs.m_size;
			char* t_buffer = m_buffer;
			m_buffer = new char[m_size + 1];

			strcpy(m_buffer, t_buffer);
			strcat(m_buffer, rhs.m_buffer);
			terminate();

			return *this;

		}

		String& const operator+=(const String& rhs) {

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
		friend void printf(const String& string, int& num , Args&& ... args);
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
	void printf(const String& string, int& num, Args&& ... args) {

		//std::unordered_map<int, char> cmap; //character map
		//std::unordered_map<int, char> fmap; //format specificer map with specifier location within a string

		//for (int i = 0; i < string.m_size; i++) {

		//	cmap[i] = string.m_buffer[i];

		//}

		//for (int i = 0; i < cmap.size(); i++) {

		//	if (cmap[i] == '%')
		//		fmap[i + 1] = cmap[i + 1];

		//}

		//might redo this

		int* specifier_loc;
		int* spec_buffer = new int[256];
		int num_specifiers = 0;

		for ( int i = 0; i < string.m_size; i++) {

			if (string.m_buffer[i] == '%') {

				spec_buffer[num_specifiers] = i;
				
				num_specifiers++;

			}

		}

		specifier_loc = new int[num_specifiers];

		
		for (int i = 0; i < num_specifiers; i++) {

			specifier_loc[i] = spec_buffer[i];

		}

	}

	

}