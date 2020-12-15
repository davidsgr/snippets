#include <memory>
#include <iostream>

int main(void)
{
    std::cout << sizeof(std::shared_ptr<int>) << std::endl;
    return 0;
}
