
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

        std::string day6(const std::string& input, bool verbose, int days)
        {
            std::vector<long long> buckets(9, 0);
            std::vector<long long> nextBuckets(9, 0);

            std::list<int> numbers = readInput(input);

            for (auto it = numbers.begin(); it != numbers.end(); ++it)
                ++buckets[*it];

            if (verbose)
            {
                std::cout << "Day " << 0 << ": ";
                for (size_t i = 0; i < 9; ++i)
                    std::cout << "(" << i << "," << buckets[i] << ")";
                std::cout << std::endl;
            }

            for (size_t day = 1; day < days + 1; ++day)
            {
                for (size_t i = 8; i > 0; --i)
                    nextBuckets[i - 1] = buckets[i];
                nextBuckets[8] = buckets[0];
                nextBuckets[6] += buckets[0];

                for (size_t i = 0; i < 9; ++i)
                    buckets[i] = nextBuckets[i];

                if (verbose)
                {
                    std::cout << "Day " << day << ": ";
                    for (size_t i = 0; i < 9; ++i)
                        std::cout << "(" << i << "," << buckets[i] << ")";
                    std::cout << std::endl;
                }
            }

            long long sum = 0;
            for (size_t i = 0; i < 9; ++i)
                sum += buckets[i];

            std::stringstream result;
            result << sum;

            return result.str();
        }
 
        std::string day6_1(const std::string& input, bool verbose)
        {
            return day6(input, verbose, 80);
        }

        std::string day6_2(const std::string& input, bool verbose)
        {
            return day6(input, verbose, 256);
        }
    }
}