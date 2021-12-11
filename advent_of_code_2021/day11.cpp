
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace mbk
{
    namespace advent_of_code_2021
    {
        std::vector<std::vector<size_t>> readInput(const std::string& input)
        {
            std::ifstream file(input);

            std::list<std::string> lines;
            while (file.peek() != EOF)
            {
                std::string line;
                std::getline(file, line);
                lines.push_back(line);
            }

            std::vector<std::vector<size_t>> matrix(lines.size(), std::vector<size_t>(lines.front().size(), 0));
            size_t row = 0;
            for (auto it = lines.begin(); it != lines.end(); ++it, ++row)
                for (size_t column = 0; column < it->size(); ++column)
                    matrix[row][column] = std::stoi(it->substr(column, 1));

            return matrix;
        }

        void printMatrix(const std::vector<std::vector<size_t>>& matrix)
        {
            for (size_t row = 0; row != matrix.size(); ++row)
            {
                for (size_t column = 0; column != matrix[row].size(); ++column)
                    std::cout << matrix[row][column];
                std::cout << std::endl;
            }
        }

        struct MatrixPosition
        {
            MatrixPosition(size_t row, size_t column) : _row(row), _column(column) {}
            size_t _row;
            size_t _column;

        };
        bool operator<(const MatrixPosition& p1, const MatrixPosition& p2)
        {
            if (p1._row == p2._row)
                return p1._column < p2._column;
            else
                return p1._row < p2._row;
        }

        std::list<MatrixPosition> flash(std::vector<std::vector<size_t>>& matrix, MatrixPosition flashPosition)
        {
            std::list<MatrixPosition> moreFlashes;

            if (flashPosition._row > 0)
            {
                if (flashPosition._column > 0)
                {
                    matrix[flashPosition._row - 1][flashPosition._column - 1] += 1;
                    if (matrix[flashPosition._row - 1][flashPosition._column - 1] > 9)
                        moreFlashes.push_back(MatrixPosition(flashPosition._row - 1, flashPosition._column - 1));
                }
                matrix[flashPosition._row - 1][flashPosition._column] += 1;
                if (matrix[flashPosition._row - 1][flashPosition._column] > 9)
                    moreFlashes.push_back(MatrixPosition(flashPosition._row - 1, flashPosition._column));
                if (flashPosition._column < matrix[flashPosition._row].size() - 1)
                {
                    matrix[flashPosition._row - 1][flashPosition._column + 1] += 1;
                    if (matrix[flashPosition._row - 1][flashPosition._column + 1] > 9)
                        moreFlashes.push_back(MatrixPosition(flashPosition._row - 1, flashPosition._column + 1));
                }
            }
            if (flashPosition._column > 0)
            {
                matrix[flashPosition._row][flashPosition._column - 1] += 1;
                if (matrix[flashPosition._row][flashPosition._column - 1] > 9)
                    moreFlashes.push_back(MatrixPosition(flashPosition._row, flashPosition._column - 1));
            }
            matrix[flashPosition._row][flashPosition._column] += 1;
            if (flashPosition._column < matrix[flashPosition._row].size() - 1)
            {
                matrix[flashPosition._row][flashPosition._column + 1] += 1;
                if (matrix[flashPosition._row][flashPosition._column + 1] > 9)
                    moreFlashes.push_back(MatrixPosition(flashPosition._row, flashPosition._column + 1));
            }
            if (flashPosition._row < matrix.size() - 1)
            {
                if (flashPosition._column > 0)
                {
                    matrix[flashPosition._row + 1][flashPosition._column - 1] += 1;
                    if (matrix[flashPosition._row + 1][flashPosition._column - 1] > 9)
                        moreFlashes.push_back(MatrixPosition(flashPosition._row + 1, flashPosition._column - 1));
                }
                matrix[flashPosition._row + 1][flashPosition._column] += 1;
                if (matrix[flashPosition._row + 1][flashPosition._column] > 9)
                    moreFlashes.push_back(MatrixPosition(flashPosition._row + 1, flashPosition._column));
                if (flashPosition._column < matrix[flashPosition._row].size() - 1)
                {
                    matrix[flashPosition._row + 1][flashPosition._column + 1] += 1;
                    if (matrix[flashPosition._row + 1][flashPosition._column + 1] > 9)
                        moreFlashes.push_back(MatrixPosition(flashPosition._row + 1, flashPosition._column + 1));
                }
            }

            return moreFlashes;
        }

        size_t simulateStep(std::vector<std::vector<size_t>>& matrix)
        {
            std::list<MatrixPosition> willFlash;
            for (size_t row = 0; row < matrix.size(); ++row)
            {
                for (size_t column = 0; column < matrix[row].size(); ++column)
                {
                    matrix[row][column] += 1;
                    if (matrix[row][column] > 9)
                        willFlash.push_back(MatrixPosition(row, column));
                }
            }

            std::set<MatrixPosition> flashed;
            while (willFlash.size() > 0)
            {
                MatrixPosition flashPosition = willFlash.front();
                willFlash.pop_front();
                if (flashed.find(flashPosition) != flashed.end())
                    continue;
                auto moreFlashes = flash(matrix, flashPosition);
                flashed.insert(flashPosition);
                for (auto it = moreFlashes.begin(); it != moreFlashes.end(); ++it)
                    willFlash.push_back(*it);
            }

            for (auto it = flashed.begin(); it != flashed.end(); ++it)
                matrix[it->_row][it->_column] = 0;

            return flashed.size();
        }

        std::string day11_1(const std::string& input, bool verbose)
        {
            std::vector<std::vector<size_t>> matrix = readInput(input);

            if (verbose)
            {
                std::cout << "Step 0:" << std::endl;
                printMatrix(matrix);
            }

            size_t count = 0;
            for (size_t i = 0; i < 100; ++i)
            {
                size_t flashes = simulateStep(matrix);
                if (verbose)
                {
                    std::cout << "Step " << i + 1 << ":" << std::endl;
                    printMatrix(matrix);
                    std::cout << "Flashes: " << flashes << std::endl << std::endl;
                }

                count += flashes;
            }

            std::stringstream result;
            result << count;

            return result.str();
        }

        std::string day11_2(const std::string& input, bool verbose)
        {
            std::vector<std::vector<size_t>> matrix = readInput(input);

            if (verbose)
            {
                std::cout << "Step 0:" << std::endl;
                printMatrix(matrix);
            }

            size_t totalSize = matrix.size() * matrix[0].size();

            size_t stepCount = 0;
            while (true)
            {
                ++stepCount;
                size_t flashes = simulateStep(matrix);
                if (verbose)
                {
                    std::cout << "Step " << stepCount << ":" << std::endl;
                    printMatrix(matrix);
                    std::cout << "Flashes: " << flashes << std::endl << std::endl;
                }

                if (flashes == totalSize)
                    break;
            }

            std::stringstream result;
            result << stepCount;

            return result.str();
        }
    }
}