#include <iostream>
#include "String.h"

int main() {

    cString::String string = "Hello";
    cString::String sub = string.substr(0, 2);

    std::cout << string << '\n';
    std::cout << sub << '\n';

    cString::String new_string = "A B";
    new_string.append("B");

    new_string.prepend("A");

    std::cout << new_string[2] << std::endl;

    std::cin.get();
    
}
