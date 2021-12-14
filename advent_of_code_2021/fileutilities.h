#ifndef INC_MBK_ADVENTOFCODE2021_FILEUTILITIES_H
#define INC_MBK_ADVENTOFCODE2021_FILEUTILITIES_H

#include <list>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        namespace file_utilities
        {
            std::list<std::string> readLines(const std::string& path);
        }
    }
}

#endif
