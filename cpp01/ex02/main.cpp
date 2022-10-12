#include <iostream>
#include <string>

int main()
{
    std::string str;
    std::string *stringPTR;
    std::string stringREF;
    str = "HI THIS IS BRAIN";
    stringPTR = &str;
    stringREF = str;
    std::cout << "Printing memory addresses" << std::endl;
    std::cout << &str << std::endl;
    std::cout << &stringPTR << std::endl;
    std::cout << &stringREF << std::endl;
    std::cout << "Printing values" << std::endl;
    std::cout << str << std::endl;
    std::cout << stringPTR << std::endl;
    std::cout << stringREF << std::endl;
}