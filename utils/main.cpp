#include <iostream>
#include "file.h"

int main()
{
    File f;
    const int result = f.init("example.txt");

    

    std::vector<std::string> lines = f.read_all_lines();
    
    for(unsigned short n = 0; n < lines.size(); n++)
        std::cout << n << ": " << lines[n] << std::endl;

    std::string line = "";
    std::cin >> line;

    f.delete_line(f.get_line_index(line));
    return 0;
}