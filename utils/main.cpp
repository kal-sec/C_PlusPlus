#include <iostream>
#include "file.h"

int main()
{
    File f;
    const int result = f.init("example.txt");

    

    std::vector<std::string> lines = f.read_all_lines();
    
    for(unsigned short n = 0; n < lines.size(); n++)
        std::cout << n << ": " << lines[n] << std::endl;

    int lnIdx = 0;
    std::cin >> lnIdx;

    f.delete_line(lnIdx);
    return 0;
}