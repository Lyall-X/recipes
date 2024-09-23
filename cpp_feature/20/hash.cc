#include <iostream>
#include <string>

int main()
{
    std::size_t num = std::hash<std::string>{}("");
    std::cout << num % 15 << std::endl;
    std::cout << num % 14 << std::endl;
    return 0;
}