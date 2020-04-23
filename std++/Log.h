#pragma once
#include <iostream>
#include <string>

enum LogType {
	WARNING,
	ERROR,
	STATE,
	INFO,
	DATA,
	CLASS_INFO
};

template <typename T>
class Log {
private:
	T m_type;
	char* log_buffer;
public:
	
};