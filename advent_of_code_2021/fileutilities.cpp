#include "fileutilities.h"

#include <fstream>

namespace mbk
{
    namespace advent_of_code_2021
    {
        namespace file_utilities
        {
            std::list<std::string> readLines(const std::string& path)
            {
                std::ifstream file(path);

                std::list<std::string> lines;
                while (file.peek() != EOF)
                {
                    std::string line;
                    std::getline(file, line);
                    lines.push_back(line);
                }

                return lines;
            }
        }
    }
}
