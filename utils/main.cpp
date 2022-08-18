#include <iostream>
#include "file.h"

int main()
{
    File f;
    const int result = f.init("example.txt");

    std::cout << "***** INIT RESULT *****" << std::endl;
    std::cout << "VALUE: " << result << std::endl;
    return 0;
}