
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        std::string day1(const std::string& input, bool verbose /* = false*/)
        {
            std::ifstream file(input);
            int increaseCount = 0;

            int lastDepth = -1;
            std::string row;
            while (std::getline(file, row))
            {
                int depth = std::stoi(row);
                if (lastDepth > 0)
                {
                    bool deeper = depth > lastDepth;
                    if (deeper)
                        ++increaseCount;

                    if (verbose)
                        std::cout << depth << " (" << (deeper ? "increased" : "decreased") << ")" << std::endl;
                }
                else
                {
                    if (verbose)
                        std::cout << depth << " (N/A - no previous measurement)" << std::endl;
                }

                lastDepth = depth;
            }

            std::stringstream result;
            result << increaseCount;

            return result.str();
        }
    }
}
