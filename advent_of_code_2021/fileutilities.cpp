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

            std::vector<std::vector<size_t>> readMatrix(const std::string& path)
            {
                std::list<std::string> lines = readLines(path);

                std::vector<std::vector<size_t>> matrix(lines.size(), std::vector<size_t>(lines.front().size(), 0));
                size_t row = 0;
                for (auto line = lines.begin(); line != lines.end(); ++line, ++row)
                    for (size_t column = 0; column < line->size(); ++column)
                        matrix[row][column] = std::stoi(line->substr(column, 1));

                return matrix;
            }
        }
    }
}
