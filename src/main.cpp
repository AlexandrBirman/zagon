#include <iostream>
#include <cstdlib>
#include "hello.h"

int main()
{
    Hello h;
    std::cout << h.say() << std::endl;
    return EXIT_SUCCESS;
}
