
#include "fileutilities.h"

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace mbk
{
    namespace advent_of_code_2021
    {
        struct Position
        {
            Position(size_t cost, size_t row, size_t column, size_t estimated) : _cost(cost), _row(row), _column(column), _estimated(estimated) {}

            size_t _cost;
            size_t _row;
            size_t _column;
            size_t _estimated;
        };

        void insertPosition(std::list<Position*>& possibleNextPosition, size_t previousCost, size_t row, size_t column, const std::vector<std::vector<size_t>>& matrix)
        {
            size_t cost = previousCost + matrix[row][column];
            size_t estimatedRemainingCost = matrix.size() - row - 1 + matrix[0].size() - column - 1;
            for (auto it = possibleNextPosition.begin(); it != possibleNextPosition.end(); ++it)
            {
                if (cost + estimatedRemainingCost < (*it)->_cost + (*it)->_estimated)
                {
                    possibleNextPosition.insert(it, new Position(cost, row, column, estimatedRemainingCost));
                    return;
                }
            }

            possibleNextPosition.push_back(new Position(cost, row, column, estimatedRemainingCost));
        }

        std::string day15(std::vector<std::vector<size_t>> matrix, bool verbose)
        {
            if (verbose)
            {
                for (auto it = matrix.begin(); it != matrix.end(); ++it)
                {
                    for (auto jt = it->begin(); jt != it->end(); ++jt)
                        std::cout << *jt;
                    std::cout << std::endl;
                }
            }

            std::list<Position*> possibleNextPositions;
            possibleNextPositions.push_back(new Position(0, 0, 0, matrix.size() + matrix[0].size() - 2));

            std::map<size_t, std::set<size_t>> visited;
            size_t totalCost = 0;
            while (true)
            {
                if (possibleNextPositions.size() < 1)
                    throw 0;

                Position* possiblePosition = possibleNextPositions.front();
                possibleNextPositions.pop_front();

                if (visited.find(possiblePosition->_row) == visited.end() || visited[possiblePosition->_row].find(possiblePosition->_column) == visited[possiblePosition->_row].end())
                {
                    if (possiblePosition->_column == matrix[0].size() - 1 &&
                        possiblePosition->_row == matrix.size() - 1)
                    {
                        totalCost = possiblePosition->_cost;
                        break;
                    }

                    if (possiblePosition->_row > 0)
                        insertPosition(possibleNextPositions, possiblePosition->_cost, possiblePosition->_row - 1, possiblePosition->_column, matrix);
                    if (possiblePosition->_column > 0)
                        insertPosition(possibleNextPositions, possiblePosition->_cost, possiblePosition->_row, possiblePosition->_column - 1, matrix);
                    if (possiblePosition->_row < matrix.size() - 1)
                        insertPosition(possibleNextPositions, possiblePosition->_cost, possiblePosition->_row + 1, possiblePosition->_column, matrix);
                    if (possiblePosition->_column < matrix[0].size() - 1)
                        insertPosition(possibleNextPositions, possiblePosition->_cost, possiblePosition->_row, possiblePosition->_column + 1, matrix);

                    if (visited.find(possiblePosition->_row) == visited.end())
                        visited[possiblePosition->_row] = std::set<size_t>();
                    visited[possiblePosition->_row].insert(possiblePosition->_column);
                }

                delete possiblePosition;
            }

            std::stringstream result;
            result << totalCost;

            return result.str();
        }
 
        std::vector<std::vector<size_t>> scaleVector(const std::vector<std::vector<size_t>>& original, size_t times)
        {
            std::vector<std::vector<size_t>> scaled(original.size() * times, std::vector<size_t>(original[0].size() * times, 0));

            for (size_t row = 0; row < original.size(); ++row)
            {
                for (size_t column = 0; column < original[0].size(); ++column)
                {
                    size_t value = original[row][column];
                    for (size_t extraRows = 0; extraRows < times; ++extraRows)
                        for (size_t extraColumns = 0; extraColumns < times; ++extraColumns)
                            scaled[row + original.size() * extraRows][column + original[0].size() * extraColumns] = (((value - 1) + extraRows + extraColumns) % 9) + 1;
                }
            }

            return scaled;
        }

        std::string day15_1(const std::string& input, bool verbose)
        {
            std::vector<std::vector<size_t>> matrix = file_utilities::readMatrix(input);

            return day15(matrix, verbose);
        }

        std::string day15_2(const std::string& input, bool verbose)
        {
            std::vector<std::vector<size_t>> matrix = scaleVector(file_utilities::readMatrix(input), 5);

            return day15(matrix, verbose);
        }
    }
}