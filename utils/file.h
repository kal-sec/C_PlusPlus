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
    enum WRITE_MODE
    {
        APPEND,
        FIRST,
        INDEX,
        OVERRIDE
    };

    enum WRITE_ERROR
    {
        INVALID_PATH,
        FILE_OPEN_ERROR,
        FILE_OPEN_TMP_ERROR,
        INVALID_INDEX,
        DELETE_ERROR,
        RENAME_ERROR,
        NONE
    };

    const short unsigned init(std::string _path)
    {
        if (_path == "")
            return 1;

        inputStream.open(_path);

        if (inputStream.fail())
        {
            outputStream.open(_path);
            outputStream << "";
            outputStream.close();
        }

        inputStream.close();

        filePath = _path;
        return 0;
    }

    std::vector<std::string> read_all_lines()
    {
        std::string tmpLine = "";
        std::vector<std::string> data = std::vector<std::string>();

        if (filePath.length() <= 0)
        {
            data.push_back("-1");
            return data;
        }

        inputStream = std::ifstream();
        inputStream.open(filePath);

        if (inputStream.fail())
        {
            data.push_back("-2");
            return data;
        }

        while (std::getline(inputStream, tmpLine))
            data.push_back(tmpLine);

        inputStream.close();
        return data;
    }
    std::string read_line(short unsigned _lnIdx)
    {
        std::string data = "";
        std::string tmpLine = "";

        if (filePath.length() <= 0)
        {
            data = "-1";
            return data;
        }

        inputStream = std::ifstream();
        inputStream.open(filePath);

        if (inputStream.fail())
        {
            data = "-2";
            inputStream.close();
            return data;
        }

        int unsigned idx = 0;

        while (std::getline(inputStream, tmpLine))
        {
            if (idx == _lnIdx)
            {
                data = tmpLine;
                inputStream.close();

                return data;
            }

            idx++;
        }

        data = "";
        inputStream.close();
        return data;
    }

    const WRITE_ERROR write_line(std::string _ln, WRITE_MODE _wm, short unsigned _lnIdx = -1)
    {
        if (filePath.length() <= 0)
            return WRITE_ERROR::INVALID_PATH;

        inputStream = std::ifstream();
        outputStream = std::ofstream();

        std::string outputPath = filePath + ".tmp";

        inputStream.open(filePath);
        outputStream.open(outputPath);

        if (inputStream.fail())
            return WRITE_ERROR::FILE_OPEN_ERROR;

        if (outputStream.fail())
            return WRITE_ERROR::FILE_OPEN_TMP_ERROR;

        std::string tmpLine = "";

        switch (_wm)
        {
        case WRITE_MODE::APPEND:
        {

            while (std::getline(inputStream, tmpLine))
                outputStream << tmpLine << std::endl;

            outputStream << _ln << std::endl;

            break;
        }
        case WRITE_MODE::FIRST:
        {
            outputStream << _ln << std::endl;

            while (std::getline(inputStream, tmpLine))
                outputStream << tmpLine << std::endl;

            break;
        }
        case WRITE_MODE::INDEX:
        {
            if (_lnIdx == -1)
                return WRITE_ERROR::INVALID_INDEX;

            int idx = 0;
            while (std::getline(inputStream, tmpLine))
            {
                if (_lnIdx == idx)
                    outputStream << _ln << std::endl;

                outputStream << tmpLine << std::endl;
                idx++;
            }

            break;
        }
        case WRITE_MODE::OVERRIDE:
        {
            outputStream << _ln << std::endl;
            break;
        }
        }

        inputStream.close();
        outputStream.close();

        char inPath[filePath.size() + 1];
        char outPath[outputPath.size() + 1];

        for (short unsigned n = 0; n < filePath.size(); n++)
            inPath[n] = filePath[n];

        for (short unsigned n = 0; n < outputPath.size(); n++)
            outPath[n] = outputPath[n];

        inPath[filePath.size()] = '\0';
        outputPath[outputPath.size()] = '\0';

        const short deleteIdx = std::remove(inPath);
        const short renameIdx = std::rename(outPath, inPath);

        if (deleteIdx != 0)
            return WRITE_ERROR::DELETE_ERROR;

        if (renameIdx != 0)
            return WRITE_ERROR::RENAME_ERROR;

        return WRITE_ERROR::NONE;
    }
};
