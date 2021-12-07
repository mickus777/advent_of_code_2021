
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
        namespace day_7
        {
            std::list<int> readInput(const std::string& input)
            {
                std::ifstream file(input);

                std::string row;
                std::getline(file, row);

                std::list<int> numbers;
                size_t lastIndex = 0;
                for (size_t index = row.find(','); index != std::string::npos; index = row.find(',', index + 1))
                {
                    numbers.push_back(std::stoi(row.substr(lastIndex, index - lastIndex)));

                    lastIndex = index + 1;
                }
                numbers.push_back(std::stoi(row.substr(lastIndex)));

                return numbers;
            }
        }

        std::string day7(const std::string& input, bool verbose, bool exponential)
        {
            std::list<int> positions = day_7::readInput(input);

            int largest = 0;
            for (auto it = positions.begin(); it != positions.end(); ++it)
                if (*it >= largest)
                    largest = *it;

            std::vector<size_t> crabCount = std::vector<size_t>(largest + 1, 0);
            std::vector<size_t> totalCosts = std::vector<size_t>(largest + 1, 0);

            for (auto it = positions.begin(); it != positions.end(); ++it)
                crabCount[*it] += 1;

            {
                int runningTotal = 0;
                int multiplier = 0;
                int crabs = 0;
                for (size_t i = 0; i < crabCount.size(); ++i)
                {
                    runningTotal += multiplier;
                    totalCosts[i] += runningTotal;
                    multiplier += crabCount[i];
                    if (exponential)
                        multiplier += crabs;
                    crabs += crabCount[i];
                }
            }

            {
                int runningTotal = 0;
                int multiplier = 0;
                int crabs = 0;
                for (int i = crabCount.size() - 1; i >= 0; --i)
                {
                    runningTotal += multiplier;
                    totalCosts[i] += runningTotal;
                    multiplier += crabCount[i];
                    if (exponential)
                        multiplier += crabs;
                    crabs += crabCount[i];
                }
            }

            if (verbose)
                for (size_t i = 0; i < totalCosts.size(); ++i)
                    std::cout << i << ": " << totalCosts[i] << std::endl;

            size_t bestCost = totalCosts[0];
            for (size_t i = 0; i < totalCosts.size(); ++i)
            {
                if (totalCosts[i] > bestCost)
                    break;

                bestCost = totalCosts[i];
            }

            std::stringstream result;
            result << bestCost;

            return result.str();
        }
 
        std::string day7_1(const std::string& input, bool verbose)
        {
            return day7(input, verbose, false);
        }

        std::string day7_2(const std::string& input, bool verbose)
        {
            return day7(input, verbose, true);
        }
    }
}