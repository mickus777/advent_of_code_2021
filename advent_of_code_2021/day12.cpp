
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        std::map<std::string, std::list<std::string>> readInput(const std::string& input)
        {
            std::map<std::string, std::list<std::string>> nodes;

            std::ifstream file(input);
            while (file.peek() != EOF)
            {
                std::string line;
                std::getline(file, line);

                size_t divisor = line.find('-');
                std::string from = line.substr(0, divisor);
                std::string to = line.substr(divisor + 1);
                if (nodes.find(from) == nodes.end())
                    nodes[from] = std::list<std::string>();
                nodes[from].push_back(to);
                if (nodes.find(to) == nodes.end())
                    nodes[to] = std::list<std::string>();
                nodes[to].push_back(from);
            }

            return nodes;
        }

        bool isLower(const std::string& text)
        {
            for (auto it = text.begin(); it != text.end(); ++it)
                if (!islower(*it))
                    return false;
            return true;
        }

        bool find(const std::list<std::string>& texts, const std::string& text)
        {
            for (auto it = texts.begin(); it != texts.end(); ++it)
                if (*it == text)
                    return true;
            return false;
        }

        struct Journey
        {
            Journey() : _smallVisitedTwice(false) {}
            Journey(const std::list<std::string>& other) : _caves(other.begin(), other.end()), _smallVisitedTwice(false) {}
            Journey(const Journey& other) : _caves(other._caves.begin(), other._caves.end()), _smallVisitedTwice(other._smallVisitedTwice) {}

            std::list<std::string> _caves;
            bool _smallVisitedTwice;
        };

        std::string day12_1(const std::string& input, bool verbose)
        {
            std::map<std::string, std::list<std::string>> complex = readInput(input);

            if (verbose)
            {
                std::cout << "Complex:" << std::endl;
                for (auto it = complex.begin(); it != complex.end(); ++it)
                {
                    std::cout << it->first << ": ";
                    for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
                        std::cout << *jt << ",";
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            std::list<std::list<std::string>> journeys;
            std::list<std::string> startJourney;
            startJourney.push_back("start");
            journeys.push_back(startJourney);

            std::list<std::list<std::string>> pathsToEnd;
            while (journeys.size() > 0)
            {
                std::list<std::string> journey = journeys.front();
                journeys.pop_front();

                std::string currentCave = journey.back();
                if (currentCave == "end")
                {
                    pathsToEnd.push_back(journey);
                    continue;
                }

                for (auto neighboringCave = complex[currentCave].begin(); neighboringCave != complex[currentCave].end(); ++neighboringCave)
                {
                    if (!isLower(*neighboringCave) || !find(journey, *neighboringCave))
                    {
                        std::list<std::string> newJourney(journey.begin(), journey.end());
                        newJourney.push_back(*neighboringCave);
                        journeys.push_back(newJourney);
                    }
                }
            }

            if (verbose)
            {
                std::cout << "Journeys:" << std::endl;
                for (auto it = pathsToEnd.begin(); it != pathsToEnd.end(); ++it)
                {
                    for (auto jt = it->begin(); jt != it->end(); ++jt)
                        std::cout << *jt << ",";
                    std::cout << std::endl;
                }
            }

            std::stringstream result;
            result << pathsToEnd.size();

            return result.str();
        }

        std::string day12_2(const std::string& input, bool verbose)
        {
            std::map<std::string, std::list<std::string>> complex = readInput(input);

            if (verbose)
            {
                std::cout << "Complex:" << std::endl;
                for (auto it = complex.begin(); it != complex.end(); ++it)
                {
                    std::cout << it->first << ": ";
                    for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
                        std::cout << *jt << ",";
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            std::list<Journey> journeys;
            Journey startJourney;
            startJourney._caves.push_back("start");
            journeys.push_back(startJourney);

            std::list<Journey> pathsToEnd;
            while (journeys.size() > 0)
            {
                Journey journey = journeys.front();
                journeys.pop_front();

                std::string currentCave = journey._caves.back();
                if (currentCave == "end")
                {
                    pathsToEnd.push_back(journey);
                    continue;
                }

                for (auto neighboringCave = complex[currentCave].begin(); neighboringCave != complex[currentCave].end(); ++neighboringCave)
                {
                    if (*neighboringCave == "start")
                        continue;

                    bool smallCave = isLower(*neighboringCave);
                    bool alreadyVisited = find(journey._caves, *neighboringCave);
                    if (smallCave && alreadyVisited && journey._smallVisitedTwice)
                        continue;

                    Journey newJourney;
                    newJourney._caves.assign(journey._caves.begin(), journey._caves.end());
                    newJourney._caves.push_back(*neighboringCave);
                    newJourney._smallVisitedTwice = journey._smallVisitedTwice || smallCave && alreadyVisited;
                    journeys.push_back(newJourney);
                }
            }

            if (verbose)
            {
                std::cout << "Journeys:" << std::endl;
                for (auto it = pathsToEnd.begin(); it != pathsToEnd.end(); ++it)
                {
                    for (auto jt = it->_caves.begin(); jt != it->_caves.end(); ++jt)
                        std::cout << *jt << ",";
                    std::cout << std::endl;
                }
            }

            std::stringstream result;
            result << pathsToEnd.size();

            return result.str();
        }
    }
}
