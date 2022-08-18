#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

class File
{
    private:
        std::ifstream inputStream = std::ifstream();
        std::ofstream outputStream = std::ofstream();

        std::string fileName = std::string();
        std::string filePath = std::string();

    public:
        const short unsigned init(std::string _path)
        {
            if(_path == "")
                return 1;
            
            outputStream.open(filePath);
            outputStream << "";
            outputStream.close();    

            filePath = _path;
            return 0;
        }
};
