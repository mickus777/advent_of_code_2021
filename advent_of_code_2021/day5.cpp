
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace mbk
{
    namespace advent_of_code_2021
    {
        struct Line
        {
            size_t _startX;
            size_t _startY;
            size_t _endX;
            size_t _endY;
        };

        std::list<Line> getLines(const std::string& input)
        {
            std::list<Line> lines;

            std::ifstream file(input);

            while (file.peek() != EOF)
            {
                std::string row;
                std::getline(file, row);
                size_t commaIndex = row.find(',');
                Line line;
                line._startX = std::stoi(row.substr(0, commaIndex));
                size_t spaceIndex = row.find(' ');
                line._startY = std::stoi(row.substr(commaIndex + 1, spaceIndex - commaIndex - 1));
                commaIndex = row.find(',', spaceIndex);
                line._endX = std::stoi(row.substr(spaceIndex + 4, commaIndex - spaceIndex - 4));
                line._endY = std::stoi(row.substr(commaIndex + 1));
                lines.push_back(line);
            }

            return lines;
        }

        size_t max(size_t v1, size_t v2)
        {
            return v1 > v2 ? v1 : v2;
        }

        std::string day5(const std::string& input, bool verbose, bool disallowDiagonals)
        {
            std::list<Line> lines = getLines(input);

            size_t maxX = 0;
            size_t maxY = 0;

            for (auto line = lines.begin(); line != lines.end(); ++line)
            {
                maxX = max(maxX, line->_startX);
                maxX = max(maxX, line->_endX);
                maxY = max(maxY, line->_startY);
                maxY = max(maxY, line->_endY);
            }
            maxX += 1;
            maxY += 1;

            std::vector<std::vector<int>> matrix(maxX, std::vector<int>(maxY, 0));
            for (auto line = lines.begin(); line != lines.end(); ++line)
            {
                int dx = line->_endX - static_cast<int>(line->_startX);
                int dy = line->_endY - static_cast<int>(line->_startY);
                if (disallowDiagonals && dx != 0 && dy != 0)
                    continue;
                if (dx != 0)
                    dx = (dx > 0 ? 1 : -1);
                if (dy != 0)
                    dy = (dy > 0 ? 1 : -1);

                int x = line->_startX;
                int y = line->_startY;
                while (x != line->_endX || y != line->_endY)
                {
                    ++matrix[x][y];
                    x += dx;
                    y += dy;
                }
                ++matrix[x][y];
            }

            size_t count = 0;
            for (size_t x = 0; x < maxX; ++x)
                for (size_t y = 0; y < maxY; ++y)
                    if (matrix[x][y] > 1)
                        ++count;

            if (verbose)
            {
                for (size_t y = 0; y < maxY; ++y)
                {
                    for (size_t x = 0; x < maxX; ++x)
                        std::cout << matrix[x][y];
                    std::cout << std::endl;
                }
            }

            std::stringstream result;
            result << count;

            return result.str();
        }

        std::string day5_1(const std::string& input, bool verbose)
        {
            return day5(input, verbose, true);
        }

        std::string day5_2(const std::string& input, bool verbose)
        {
            return day5(input, verbose, false);
        }
    }
}
