
#include "fileutilities.h"

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
        struct Position
        {
            Position(size_t row, size_t column) : _row(row), _column(column) {}

            size_t _row;
            size_t _column;
        };

        Position toPosition(const std::string& text)
        {
            size_t i = text.find(',');
            return Position(std::stoi(text.substr(i + 1)), std::stoi(text.substr(0, i)));
        }

        struct Fold
        {
            Fold(size_t count, bool row) : _count(count), _row(row) {}

            size_t _count;
            bool _row;
        };

        Fold toFold(const std::string& text)
        {
            return Fold(std::stoi(text.substr(13)), text.substr(11, 1) == "y");
        }

        std::string day13(const std::string& input, bool verbose, bool doAll)
        {
            std::list<std::string> lines = file_utilities::readLines(input);

            if (verbose)
            {
                for (auto it = lines.begin(); it != lines.end(); ++it)
                    std::cout << *it << std::endl;
                std::cout << std::endl;
            }

            std::list<Position> points;
            std::list<Fold> folds;
            {
                auto it = lines.begin();
                while (it->size() > 0)
                {
                    points.push_back(toPosition(*it));
                    ++it;
                }

                ++it;
                while (it != lines.end())
                {
                    folds.push_back(toFold(*it));
                    ++it;
                }
            }

            size_t maxRow = 0;
            size_t maxColumn = 0;
            for (auto it = points.begin(); it != points.end(); ++it)
            {
                if (it->_row > maxRow)
                    maxRow = it->_row;
                if (it->_column > maxColumn)
                    maxColumn = it->_column;
            }
            maxRow += 1;
            maxColumn += 1;

            std::vector<std::vector<bool>> matrix(maxRow, std::vector<bool>(maxColumn, false));
            for (auto it = points.begin(); it != points.end(); ++it)
                matrix[it->_row][it->_column] = true;

            std::ofstream output("out.txt", std::ios::app);

            if (verbose)
            {
                for (size_t row = 0; row < maxRow; ++row)
                {
                    for (size_t column = 0; column < maxColumn; ++column)
                        output << (matrix[row][column] ? '#' : '.');
                    output << std::endl;
                }
                output << std::endl;
            }

            for (auto it = folds.begin(); it != folds.end(); ++it)
            {
                if (it->_row)
                {
                    for (int offset = 1; offset + it->_count < maxRow; ++offset)
                        for (size_t column = 0; column < maxColumn; ++column)
                            matrix[it->_count - offset][column] = matrix[it->_count - offset][column] || matrix[it->_count + offset][column];
                    maxRow = it->_count;
                }
                else
                {
                    for (int offset = 1; offset + it->_count < maxColumn; ++offset)
                        for (size_t row = 0; row < maxRow; ++row)
                            matrix[row][it->_count - offset] = matrix[row][it->_count - offset] || matrix[row][it->_count + offset];
                    maxColumn = it->_count;
                }

                if (verbose)
                {
                    for (size_t row = 0; row < maxRow; ++row)
                    {
                        for (size_t column = 0; column < maxColumn; ++column)
                            output << (matrix[row][column] ? '#' : '.');
                        output << std::endl;
                    }
                    output << std::endl;
                }

                if (!doAll)
                    break;
            }

            output.flush();
            output.close();

            size_t count = 0;
            for (size_t row = 0; row < maxRow; ++row)
                for (size_t column = 0; column < maxColumn; ++column)
                    count += (matrix[row][column] ? 1 : 0);

            std::stringstream result;
            result << count;

            return result.str();
        }

        std::string day13_1(const std::string& input, bool verbose)
        {
            return day13(input, verbose, false);
        }

        std::string day13_2(const std::string& input, bool verbose)
        {
            return day13(input, verbose, true);
        }
    }
}