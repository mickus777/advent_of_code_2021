
#include "fileutilities.h"

#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        void addMaps(std::map<char, long long>& first, const std::map<char, long long>& second)
        {
            for (auto it = second.begin(); it != second.end(); ++it)
            {
                if (first.find(it->first) == first.end())
                    first[it->first] = 0;
                first[it->first] += it->second;
            }
        }

        std::string couple(char a, char b)
        {
            std::stringstream coupling;
            coupling << a << b;
            return coupling.str();
        }

        std::map<char, long long> calculateExpansions(const std::string& pair, size_t stepCount, std::map<char, std::map<char, char>>& rules, std::map<size_t, std::map<std::string, std::map<char, long long>>>& cache)
        {
            std::map<char, long long> result;

            if (stepCount == 1)
            {
                if (result.find(pair.at(0)) == result.end())
                    result[pair.at(0)] = 0;
                result[pair.at(0)] += 1;

                return result;
            }

            char first = pair.at(0);
            char second = pair.at(1);
            char product = rules[first][second];

            std::string part1 = couple(first, product);
            if (cache.find(stepCount - 1) != cache.end() &&
                cache[stepCount - 1].find(part1) != cache[stepCount - 1].end())
                addMaps(result, cache[stepCount - 1][part1]);
            else
                addMaps(result, calculateExpansions(part1, stepCount - 1, rules, cache));
            
            std::string part2 = couple(product, second);
            if (cache.find(stepCount - 1) != cache.end() &&
                cache[stepCount - 1].find(part2) != cache[stepCount - 1].end())
                addMaps(result, cache[stepCount - 1][part2]);
            else
                addMaps(result, calculateExpansions(part2, stepCount - 1, rules, cache));

            if (cache.find(stepCount) == cache.end())
                cache[stepCount] = std::map<std::string, std::map<char, long long>>();
            cache[stepCount][pair] = result;

            return result;
        }

        std::string day14(const std::string& input, bool verbose, size_t stepCount)
        {
            std::list<std::string> lines = file_utilities::readLines(input);

            auto line = lines.begin();
            std::string polymer = *line;
            ++line;
            ++line;
            
            std::map<char, std::map<char, char>> rules;
            while (line != lines.end())
            {
                if (rules.find(line->at(0)) == rules.end())
                    rules[line->at(0)] = std::map<char, char>();
                rules[line->at(0)][line->at(1)] = line->at(6);

                ++line;
            }

            std::map<char, long long> counts;
            std::map<size_t, std::map<std::string, std::map<char, long long>>> cache;
            for (size_t i = 0; i < polymer.size() - 1; ++i)
            {
                addMaps(counts, calculateExpansions(polymer.substr(i, 2), stepCount, rules, cache));
            }
            counts[polymer.at(polymer.size() - 1)] += 1;

            long long mostCommon = 0;
            long long leastCommon = LLONG_MAX;
            for (auto it = counts.begin(); it != counts.end(); ++it)
            {
                if (it->second > mostCommon)
                    mostCommon = it->second;
                if (it->second < leastCommon)
                    leastCommon = it->second;
            }

            std::stringstream result;
            result << mostCommon - leastCommon;

            return result.str();
        }
 
        std::string day14_1(const std::string& input, bool verbose)
        {
            return day14(input, verbose, 11);
        }

        std::string day14_2(const std::string& input, bool verbose)
        {
            return day14(input, verbose, 41);
        }
    }
}