
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace mbk
{
    namespace advent_of_code_2021
    {
        std::vector<std::vector<int>> readInput(const std::string& input)
        {
            std::ifstream file(input);

            std::list<std::string> rows;
            while (file.peek() != EOF)
            {
                std::string row;
                std::getline(file, row);
                rows.push_back(row);
            }

            std::vector<std::vector<int>> matrix(rows.size(), std::vector<int>());
            size_t rowIndex = 0;
            for (auto it = rows.begin(); it != rows.end(); ++it, ++rowIndex)
            {
                std::vector<int> row(it->size(), 0);
                for (size_t i = 0; i < it->size(); ++i)
                    row[i] = std::stoi(it->substr(i, 1));
                matrix[rowIndex] = row;
            }

            return matrix;
        }

        bool neighborsGreater(const std::vector<std::vector<int>>& matrix, size_t row, size_t column)
        {
            int value = matrix[row][column];
            if (row > 0 && matrix[row - 1][column] <= value)
                return false;
            if (row < matrix.size() - 1 && matrix[row + 1][column] <= value)
                return false;
            if (column > 0 && matrix[row][column - 1] <= value)
                return false;
            if (column < matrix[0].size() - 1 && matrix[row][column + 1] <= value)
                return false;

            return true;
        }

        std::string day9_1(const std::string& input, bool verbose)
        {
            std::vector<std::vector<int>> matrix = readInput(input);

            if (verbose)
            {
                for (auto it = matrix.begin(); it != matrix.end(); ++it)
                {
                    for (auto jt = it->begin(); jt != it->end(); ++jt)
                        std::cout << *jt;
                    std::cout << std::endl;
                }
            }

            int sum = 0;
            for (size_t row = 0; row < matrix.size(); ++row)
            {
                for (size_t column = 0; column < matrix[0].size(); ++column)
                {
                    if (neighborsGreater(matrix, row, column))
                    {
                        if (verbose)
                            std::cout << matrix[row][column] << std::endl;
                        sum += matrix[row][column] + 1;
                    }
                }
            }

            std::stringstream result;
            result << sum;

            return result.str();
        }

        struct Position
        {
            Position(size_t row, size_t column) : _row(row), _column(column) {}

            size_t _row;
            size_t _column;
        };

        void appendUnmarkedNeighbors(const std::vector<std::vector<int>>& matrix, const std::vector<std::vector<bool>>& marked, std::map<int, std::list<Position>>& toMark, size_t row, size_t column)
        {
            if (row > 0 && !marked[row - 1][column] && matrix[row][column] < matrix[row - 1][column] && matrix[row - 1][column] != 9)
                toMark[matrix[row - 1][column]].push_back(Position(row - 1, column));
            if (row < matrix.size() - 1 && !marked[row + 1][column] && matrix[row][column] < matrix[row + 1][column] && matrix[row + 1][column] != 9)
                toMark[matrix[row + 1][column]].push_back(Position(row + 1, column));
            if (column > 0 && !marked[row][column - 1] && matrix[row][column] < matrix[row][column - 1] && matrix[row][column - 1] != 9)
                toMark[matrix[row][column - 1]].push_back(Position(row, column - 1));
            if (column < matrix[0].size() - 1 && !marked[row][column + 1] && matrix[row][column] < matrix[row][column + 1] && matrix[row][column + 1] != 9)
                toMark[matrix[row][column + 1]].push_back(Position(row, column + 1));
        }

        int markBasin(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>& marked, size_t row, size_t column)
        {
            std::map<int, std::list<Position>> toMark;
            for (int i = 0; i < 9; ++i)
                toMark[i] = std::list<Position>();

            toMark[matrix[row][column]].push_back(Position(row, column));

            int count = 0;
            for (int i = 0; i < 9; ++i)
            {
                while (toMark[i].size() > 0)
                {
                    Position position = toMark[i].front();
                    toMark[i].pop_front();

                    if (marked[position._row][position._column])
                        continue;

                    marked[position._row][position._column] = true;
                    ++count;
                    appendUnmarkedNeighbors(matrix, marked, toMark, position._row, position._column);
                }
            }

            for (int i = 0; i < 9; ++i)
                if (toMark[i].size() > 0)
                    throw 0;

            return count;
        }

        std::string day9_2(const std::string& input, bool verbose)
        {
            std::vector<std::vector<int>> matrix = readInput(input);

            if (verbose)
            {
                for (auto it = matrix.begin(); it != matrix.end(); ++it)
                {
                    for (auto jt = it->begin(); jt != it->end(); ++jt)
                        std::cout << *jt;
                    std::cout << std::endl;
                }
            }

            std::list<int> basins;
            std::vector<std::vector<bool>> marked(matrix.size(), std::vector<bool>(matrix[0].size(), false));

            for (size_t row = 0; row < matrix.size(); ++row)
            {
                for (size_t column = 0; column < matrix[0].size(); ++column)
                {
                    if (!marked[row][column] && matrix[row][column] != 9)
                    {
                        if (neighborsGreater(matrix, row, column))
                        {
                            int basinSize = markBasin(matrix, marked, row, column);
                            basins.push_back(basinSize);
                            if (verbose)
                            {
                                for (auto it = marked.begin(); it != marked.end(); ++it)
                                {
                                    for (auto jt = it->begin(); jt != it->end(); ++jt)
                                        std::cout << (*jt ? 1 : 0);
                                    std::cout << std::endl;
                                }
                                std::cout << basinSize << std::endl;
                            }
                        }
                    }
                }
            }

            basins.sort();

            if (verbose)
            {
                for (auto it = basins.begin(); it != basins.end(); ++it)
                    std::cout << *it;
                std::cout << std::endl;
            }

            int product = 1;
            auto it = basins.rbegin();
            for (size_t i = 0; i < 3; ++i)
            {
                product *= *it;
                ++it;
            }

            std::stringstream result;
            result << product;

            return result.str();
        }
    }
}