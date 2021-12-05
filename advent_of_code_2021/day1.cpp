
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        std::string day1_1(const std::string& input, bool verbose /* = false*/)
        {
            std::ifstream file(input);
            int increaseCount = 0;

            int lastDepth = -1;
            std::string row;
            while (std::getline(file, row))
            {
                int depth = std::stoi(row);
                if (lastDepth > 0)
                {
                    bool deeper = depth > lastDepth;
                    if (deeper)
                        ++increaseCount;

                    if (verbose)
                        std::cout << depth << " (" << (deeper ? "increased" : "decreased") << ")" << std::endl;
                }
                else
                {
                    if (verbose)
                        std::cout << depth << " (N/A - no previous measurement)" << std::endl;
                }

                lastDepth = depth;
            }

            std::stringstream result;
            result << increaseCount;

            return result.str();
        }

        class WindowStream
        {
        public:
            WindowStream(std::ifstream& input, size_t windowSize)
                : _input(input), _windowSize(windowSize)
            {
            }

            int getNext()
            {
                while (_window.size() < _windowSize)
                {
                    if (_input.peek() == EOF)
                        return 0;
                    std::string row;
                    std::getline(_input, row);
                    _window.push_back(std::stoi(row));
                }

                int total = 0;
                for (auto it = _window.begin(); it != _window.end(); ++it)
                    total += *it;

                _window.pop_front();

                return total;
            }

        private:
            std::ifstream& _input;
            std::list<int> _window;
            size_t _windowSize;
        };

        std::string day1_2(const std::string& input, bool verbose /* = false*/)
        {
            std::ifstream file(input);
            int increaseCount = 0;
            int lastTotalDepth = -1;

            WindowStream depthStream(file, 3);
            for (int totalDepth = depthStream.getNext(); totalDepth > 0; totalDepth = depthStream.getNext())
            {
                if (lastTotalDepth < 0)
                {
                    if (verbose)
                        std::cout << totalDepth << " (N/A - no previous measurement)" << std::endl;
                }
                else if (totalDepth > lastTotalDepth)
                {
                    ++increaseCount;
                    if (verbose)
                        std::cout << totalDepth << " (increased)" << std::endl;
                }
                else if (totalDepth == lastTotalDepth)
                {
                    if (verbose)
                        std::cout << totalDepth << " (no change)" << std::endl;
                }
                else
                {
                    if (verbose)
                        std::cout << totalDepth << " (decreased)" << std::endl;
                }

                lastTotalDepth = totalDepth;
            }

            std::stringstream result;
            result << increaseCount;

            return result.str();
        }
    }
}
