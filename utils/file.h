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

    enum WRITE_STATUS
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

    const WRITE_STATUS write_line(std::string _ln, WRITE_MODE _wm, short unsigned _lnIdx = -1)
    {
        if (filePath.length() <= 0)
            return WRITE_STATUS::INVALID_PATH;

        inputStream = std::ifstream();
        outputStream = std::ofstream();

        std::string outputPath = filePath + ".tmp";

        inputStream.open(filePath);
        outputStream.open(outputPath);

        if (inputStream.fail())
            return WRITE_STATUS::FILE_OPEN_ERROR;

        if (outputStream.fail())
            return WRITE_STATUS::FILE_OPEN_TMP_ERROR;

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
                return WRITE_STATUS::INVALID_INDEX;

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
            return WRITE_STATUS::DELETE_ERROR;

        if (renameIdx != 0)
            return WRITE_STATUS::RENAME_ERROR;

        return WRITE_STATUS::NONE;
    }
    const short unsigned write_all_lines(std::vector<std::string> _lines, WRITE_MODE _wm, short unsigned _lnIdx = -1)
    {
        if (filePath.length() <= 0)
            return WRITE_STATUS::INVALID_PATH;

        inputStream = std::ifstream();
        outputStream = std::ofstream();

        std::string outputPath = filePath + ".tmp";

        inputStream.open(filePath);
        outputStream.open(outputPath);

        if (inputStream.fail())
            return WRITE_STATUS::FILE_OPEN_ERROR;

        if (outputStream.fail())
            return WRITE_STATUS::FILE_OPEN_TMP_ERROR;

        std::string tmpLine = "";

        switch (_wm)
        {
        case WRITE_MODE::APPEND:
        {

            while (std::getline(inputStream, tmpLine))
                outputStream << tmpLine << std::endl;

            for (unsigned short n = 0; n < _lines.size(); n++)
                outputStream << _lines[n] << std::endl;

            break;
        }
        case WRITE_MODE::FIRST:
        {
            for (unsigned short n = 0; n < _lines.size(); n++)
                outputStream << _lines[n] << std::endl;

            while (std::getline(inputStream, tmpLine))
                outputStream << tmpLine << std::endl;

            break;
        }
        case WRITE_MODE::INDEX:
        {
            if (_lnIdx == -1)
                return WRITE_STATUS::INVALID_INDEX;

            int idx = 0;
            while (std::getline(inputStream, tmpLine))
            {
                if (_lnIdx == idx)
                {
                    for (unsigned short n = 0; n < _lines.size(); n++)
                        outputStream << _lines[n] << std::endl;
                }

                outputStream << tmpLine << std::endl;
                idx++;
            }

            break;
        }
        case WRITE_MODE::OVERRIDE:
        {
            for (unsigned short n = 0; n < _lines.size(); n++)
                outputStream << _lines[n] << std::endl;
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
            return WRITE_STATUS::DELETE_ERROR;

        if (renameIdx != 0)
            return WRITE_STATUS::RENAME_ERROR;

        return WRITE_STATUS::NONE;
    }
    const unsigned short delete_line(short unsigned _lnIdx)
    {
        if (filePath.size() <= 0)
            return -1;

        inputStream = std::ifstream();
        outputStream = std::ofstream();

        std::string tempLine = "";
        std::string outputPath = filePath + ".tmp";

        inputStream.open(filePath);
        outputStream.open(outputPath);

        if (inputStream.fail())
            return -2;

        if (outputStream.fail())
            return -3;

        int idx = 0;
        while (std::getline(inputStream, tempLine))
        {
            if (_lnIdx != idx)
                outputStream << tempLine << std::endl;

            idx++;
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

        if (deleteIdx != 0 || renameIdx != 0)
            return -4;

        return 0;
    }
    const unsigned int get_line_index(std::string _seq)
    {
        if (filePath.length() <= 0)
        {
            inputStream.close();
            return -1;
        }

        inputStream = std::ifstream();
        inputStream.open(filePath);

        if (inputStream.fail())
        {
            inputStream.close();
            return -2;
        }

        int idx = 0;
        std::string tempLine = "";

        while (std::getline(inputStream, tempLine))
        {
            int chIdx = 0;
            for (unsigned short n = 0; n < tempLine.length(); n++)
            {
                if (tempLine[n] == _seq[chIdx])
                    chIdx++;
                else
                    chIdx = 0;

                if (chIdx == _seq.length())
                {
                    inputStream.close();
                    return idx;
                }
            }

            idx++;
        }

        inputStream.close();
        return -3;
    }
};
