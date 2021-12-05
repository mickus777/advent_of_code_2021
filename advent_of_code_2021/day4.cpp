
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace mbk
{
    namespace advent_of_code_2021
    {
        struct BingoBoard
        {
            BingoBoard() : _spaces(5, std::vector<int>(5, 0)) { }

            std::vector<std::vector<int>> _spaces;
        };

        std::list<int> getNumbers(std::ifstream& input)
        {
            std::list<int> numbers;

            std::string row;
            std::getline(input, row);

            size_t index = 0;
            for (size_t spaceIndex = row.find(',', index); spaceIndex != std::string::npos; index = spaceIndex + 1, spaceIndex = row.find(',', index))
                numbers.push_back(std::stoi(row.substr(index, spaceIndex - index)));
            numbers.push_back(std::stoi(row.substr(index)));

            return numbers;
        }

        std::vector<BingoBoard> getBingoBoards(std::ifstream& input)
        {
            std::list<BingoBoard> boards;

            while (input.peek() != EOF)
            {
                BingoBoard board;

                std::string line;
                std::getline(input, line);

                for (size_t row = 0; row < 5; ++row)
                {
                    std::getline(input, line);

                    for (size_t column = 0; column < 5; ++column)
                    {
                        std::string number = line.substr(column * 3, 2);
                        if (number.at(0) == ' ')
                            number = number.substr(1);
                        board._spaces[row][column] = std::stoi(number);
                    }
                }

                boards.push_back(board);
            }

            return std::vector<BingoBoard>(boards.begin(), boards.end());
        }

        void printBoard(const BingoBoard& board)
        {
            for (size_t row = 0; row < 5; ++row)
            {
                for (size_t column = 0; column < 5; ++column)
                    std::cout << board._spaces[row][column] << " ";
                std::cout << std::endl;
            }
        }

        struct NumberPosition
        {
            NumberPosition(size_t boardIndex, size_t row, size_t column) : _boardIndex(boardIndex), _row(row), _column(column) {}

            size_t _boardIndex;
            size_t _row;
            size_t _column;
        };

        bool gameOver(const BingoBoard& board, const NumberPosition& lastCalled)
        {
            {
                int n = 0;
                for (size_t column = 0; column < 5; ++column)
                    n += board._spaces[lastCalled._row][column];
                if (n == -5)
                    return true;
            }
            {
                int n = 0;
                for (size_t row = 0; row < 5; ++row)
                    n += board._spaces[row][lastCalled._column];
                if (n == -5)
                    return true;
            }

            return false;
        }

        int calculateVictoryPoints(const BingoBoard& board)
        {
            int victoryPoints = 0;
            for (size_t row = 0; row < 5; ++row)
                for (size_t column = 0; column < 5; ++column)
                    if (board._spaces[row][column] != -1)
                        victoryPoints += board._spaces[row][column];

            return victoryPoints;
        }

        std::string day4_1(const std::string& input, bool verbose)
        {
            std::ifstream file(input);

            std::list<int> numbers = getNumbers(file);
            std::vector<BingoBoard> boards = getBingoBoards(file);
            std::map<int, std::list<NumberPosition>> numberPositions;
            for (size_t boardIndex = 0; boardIndex != boards.size(); ++boardIndex)
            {
                for (size_t row = 0; row < 5; ++row)
                {
                    for (size_t column = 0; column < 5; ++column)
                    {
                        int number = boards[boardIndex]._spaces[row][column];
                        if (numberPositions.find(number) == numberPositions.end())
                            numberPositions[number] = std::list<NumberPosition>();
                        numberPositions[number].push_back(NumberPosition(boardIndex, row, column));
                    }
                }
            }

            for (auto it = numbers.begin(); it != numbers.end(); ++it)
            {
                for (auto jt = numberPositions[*it].begin(); jt != numberPositions[*it].end(); ++jt)
                {
                    boards[(*jt)._boardIndex]._spaces[(*jt)._row][(*jt)._column] = -1;
                    if (!gameOver(boards[(*jt)._boardIndex], *jt))
                        continue;

                    int remainingPoints = calculateVictoryPoints(boards[(*jt)._boardIndex]);

                    std::stringstream result;
                    result << remainingPoints * *it;

                    return result.str();
                }
            }


            for (auto it = boards.begin(); it != boards.end(); ++it)
                printBoard(*it);

            return "";
        }
 
        std::string day4_2(const std::string& input, bool verbose)
        {
            std::ifstream file(input);

            std::list<int> numbers = getNumbers(file);
            std::vector<BingoBoard> boards = getBingoBoards(file);
            std::map<int, std::list<NumberPosition>> numberPositions;
            for (size_t boardIndex = 0; boardIndex != boards.size(); ++boardIndex)
            {
                for (size_t row = 0; row < 5; ++row)
                {
                    for (size_t column = 0; column < 5; ++column)
                    {
                        int number = boards[boardIndex]._spaces[row][column];
                        if (numberPositions.find(number) == numberPositions.end())
                            numberPositions[number] = std::list<NumberPosition>();
                        numberPositions[number].push_back(NumberPosition(boardIndex, row, column));
                    }
                }
            }

            std::set<size_t> finishedBoards;
            size_t lastBoard = 0;
            int lastNumber = -1;

            for (auto it = numbers.begin(); it != numbers.end(); ++it)
            {
                for (auto jt = numberPositions[*it].begin(); jt != numberPositions[*it].end(); ++jt)
                {
                    if (finishedBoards.find((*jt)._boardIndex) != finishedBoards.end())
                        continue;
                    boards[(*jt)._boardIndex]._spaces[(*jt)._row][(*jt)._column] = -1;
                    if (gameOver(boards[(*jt)._boardIndex], *jt))
                    {
                        finishedBoards.insert((*jt)._boardIndex);
                        lastBoard = (*jt)._boardIndex;
                    }
                }

                if (finishedBoards.size() == boards.size())
                {
                    lastNumber = *it;
                    break;
                }
            }

            int remainingPoints = calculateVictoryPoints(boards[lastBoard]);

            std::stringstream result;
            result << remainingPoints * lastNumber;

            return result.str();
        }
    }
}