#include <iostream>
#include "file.h"

int main()
{
    File f;
    const int result = f.init("example.txt");

    std::vector<std::string> lines = f.read_all_lines();
    
    for(unsigned short n = 0; n < lines.size(); n++)
        std::cout << lines[n] << std::endl;

    return 0;
}