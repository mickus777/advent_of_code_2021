
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        std::list<std::string> readInput(const std::string& input)
        {
            std::ifstream file(input);

            std::list<std::string> lines;

            while (file.peek() != EOF)
            {
                std::string line;
                std::getline(file, line);
                lines.push_back(line);
            }

            return lines;
        }

        char getMismatchedCharacter(const std::string& line)
        {
            std::list<char> chars;

            for (auto ch = line.begin(); ch != line.end(); ++ch)
            {
                if (*ch == ')')
                {
                    if (chars.size() == 0 || *chars.rbegin() != '(')
                        return ')';
                    else
                        chars.pop_back();
                }
                else if (*ch == ']')
                {
                    if (chars.size() == 0 || *chars.rbegin() != '[')
                        return ']';
                    else
                        chars.pop_back();
                }
                else if (*ch == '>')
                {
                    if (chars.size() == 0 || *chars.rbegin() != '<')
                        return '>';
                    else
                        chars.pop_back();
                }
                else if (*ch == '}')
                {
                    if (chars.size() == 0 || *chars.rbegin() != '{')
                        return '}';
                    else
                        chars.pop_back();
                }
                else
                {
                    chars.push_back(*ch);
                }
            }

            return '\0';
        }

        int score(char ch)
        {
            switch (ch)
            {
            case ')': return 3;
            case ']': return 57;
            case '}': return 1197;
            case '>': return 25137;
            default: throw 0;
            }
        }

        std::string day10_1(const std::string& input, bool verbose)
        {
            std::list<std::string> lines = readInput(input);

            int sum = 0;
            for (auto it = lines.begin(); it != lines.end(); ++it)
            {
                if (verbose)
                    std::cout << *it << std::endl;

                char mismatched = getMismatchedCharacter(*it);
                if (mismatched != '\0')
                {
                    if (verbose)
                        std::cout << "Mismatched: " << mismatched << std::endl;
                    sum += score(mismatched);
                }
            }

            std::stringstream result;
            result << sum;

            return result.str();
        }

        int scoreCompletion(char ch)
        {
            switch (ch)
            {
            case '(': return 1;
            case '[': return 2;
            case '{': return 3;
            case '<': return 4;
            default: throw 0;
            }
        }

        long long completeBrackets(const std::string& line)
        {
            std::list<char> chars;

            for (auto ch = line.begin(); ch != line.end(); ++ch)
            {
                if (*ch == ')')
                    chars.pop_back();
                else if (*ch == ']')
                    chars.pop_back();
                else if (*ch == '>')
                    chars.pop_back();
                else if (*ch == '}')
                    chars.pop_back();
                else
                    chars.push_back(*ch);
            }

            long long value = 0;
            for (auto it = chars.rbegin(); it != chars.rend(); ++it)
            {
                value *= 5;
                value += scoreCompletion(*it);
            }

            return value;
        }

        std::string day10_2(const std::string& input, bool verbose)
        {
            std::list<std::string> lines = readInput(input);

            std::list<long long> completionScores;
            for (auto it = lines.begin(); it != lines.end(); ++it)
            {
                if (verbose)
                    std::cout << *it << std::endl;

                char mismatched = getMismatchedCharacter(*it);
                if (mismatched == '\0')
                {
                    long long completionScore = completeBrackets(*it);
                    completionScores.push_back(completionScore);
                    if (verbose)
                        std::cout << "Completion: " << completionScore << std::endl;
                }
            }

            completionScores.sort();
            auto it = completionScores.begin();
            for (size_t i = 0; i < completionScores.size() / 2; ++i)
                ++it;

            if (verbose)
                for (auto jt = completionScores.begin(); jt != completionScores.end(); ++jt)
                    std::cout << *jt << std::endl;

            std::stringstream result;
            result << *it;

            return result.str();
        }
    }
}
