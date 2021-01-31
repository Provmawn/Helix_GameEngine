#include "IOManager.h" #include <string>
#include <fstream>
#include <iostream>

#include "Exception.h"
namespace helix
{
    bool IOManager::ReadFileToBuffer(const std::string &path, std::vector<char> &buffer)
    {
        std::ifstream file{ path, std::ios::binary };
        try {
            if (!file)
            {
                throw ("Could not open " + path + "\n");
                return false;
            }

        }
        catch (const Exception &exception)
        {
            std::cerr << "Exception Caught: " << exception.what() << '\n';
        }
        catch (const std::exception &exception)
        {
            std::cerr << "Unaccounted Exception Caught\n";
        }

        file.seekg(0, std::ios::end);
        auto file_size{ file.tellg() };
        std::cout << "File Size Before: " << file_size << '\n';

        file.seekg(0, std::ios::beg);
        auto beginning{ file.tellg() };
        file_size -= beginning;
        std::cout << "File Size After: " << file_size << '\n';

        buffer.resize(file_size);
        file.read(&(buffer[0]), file_size);
        file.close();

        return true;
    }
}
