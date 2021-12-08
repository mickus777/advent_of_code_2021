
#include <algorithm>
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
        struct SignalEntry
        {
            SignalEntry() : _signals(10, ""), _outputs(4, "") {}

            std::vector<std::string> _signals;
            std::vector<std::string> _outputs;
        };

        std::list<SignalEntry> readInput(const std::string& input)
        {
            std::ifstream stream(input);

            std::list<SignalEntry> entries;
            while (stream.peek() != EOF)
            {
                SignalEntry entry;
                std::string row;
                std::getline(stream, row);

                std::stringstream rowStream(row);
                for (size_t i = 0; i < 10; ++i)
                {
                    rowStream >> entry._signals[i];
                    std::sort(entry._signals[i].begin(), entry._signals[i].end());
                }
                std::string pipe;
                rowStream >> pipe;
                for (size_t i = 0; i < 4; ++i)
                {
                    rowStream >> entry._outputs[i];
                    std::sort(entry._outputs[i].begin(), entry._outputs[i].end());
                }

                entries.push_back(entry);
            }

            return entries;
        }

        std::string day8_1(const std::string& input, bool verbose)
        {
            std::list<SignalEntry> entries = readInput(input);

            size_t count = 0;
            for (auto it = entries.begin(); it != entries.end(); ++it)
            {
                for (auto jt = (*it)._outputs.begin(); jt != (*it)._outputs.end(); ++jt)
                {
                    if ((*jt).size() == 2 || (*jt).size() == 3 || (*jt).size() == 4 || (*jt).size() == 7)
                    {
                        if (verbose)
                            std::cout << *jt << " ";
                        ++count;
                    }
                }
                if (verbose)
                    std::cout << std::endl;
            }

            std::stringstream result;
            result << count;

            return result.str();
        }

        std::string findStringOfSize(const std::vector<std::string>& signals, size_t size)
        {
            for (auto signal = signals.begin(); signal != signals.end(); ++signal)
                if (signal->size() == size)
                    return *signal;

            throw 0;
        }

        std::list<std::string> findStringsOfSize(const std::vector<std::string>& signals, size_t size)
        {
            std::list<std::string> strings;

            for (auto signal = signals.begin(); signal != signals.end(); ++signal)
                if (signal->size() == size)
                    strings.push_back(*signal);

            return strings;
        }

        char findMissingChar(const std::string& original, const std::string& lesser)
        {
            for (size_t i = 0; i < lesser.size(); ++i)
                if (original[i] != lesser[i])
                    return original[i];

            return *original.rbegin();
        }

        bool containsAll(const std::string& greater, const std::string& lesser)
        {
            size_t lesserPos = 0;
            size_t greaterPos = 0;
            while (true)
            {
                if (lesserPos == lesser.size())
                {
                    return true;
                }
                else if (greaterPos == greater.size())
                {
                    return false;
                }
                else if (greater[greaterPos] == lesser[lesserPos])
                {
                    ++lesserPos;
                    ++greaterPos;
                }
                else if (greater[greaterPos] > lesser[lesserPos])
                {
                    return false;
                }
                else
                {
                    ++greaterPos;
                }
            }
        }

        std::string findSignalContainingSignal(const std::list<std::string>& signals, const std::string& signalToSearchFor)
        {
            for (auto it = signals.begin(); it != signals.end(); ++it)
                if (containsAll(*it, signalToSearchFor))
                    return *it;

            throw 0;
        }

        std::list<std::string> removeSignal(const std::list<std::string>& signals, const std::string& signalToRemove)
        {
            std::list<std::string> remainingSignals;

            for (auto it = signals.begin(); it != signals.end(); ++it)
                if (*it != signalToRemove)
                    remainingSignals.push_back(*it);

            return remainingSignals;
        }

        std::string findSignalContaining(const std::list<std::string>& signals, const char ch)
        {
            for (auto it = signals.begin(); it != signals.end(); ++it)
                for (auto jt = it->begin(); jt != it->end(); ++jt)
                    if (*jt == ch)
                        return *it;

            throw 0;
        }

        int matchValue(const std::string& output, const std::string& zero, const std::string& one, const std::string& two, const std::string& three, const std::string& four, const std::string& five, const std::string& six, const std::string& seven, const std::string& eight, const std::string& nine)
        {
            if (output == zero)
                return 0;
            else if (output == one)
                return 1;
            else if (output == two)
                return 2;
            else if (output == three)
                return 3;
            else if (output == four)
                return 4;
            else if (output == five)
                return 5;
            else if (output == six)
                return 6;
            else if (output == seven)
                return 7;
            else if (output == eight)
                return 8;
            else if (output == nine)
                return 9;
            else
                throw 0;

        }

        std::string day8_2(const std::string& input, bool verbose)
        {
            std::list<SignalEntry> entries = readInput(input);

            int total = 0;
            for (auto entry = entries.begin(); entry != entries.end(); ++entry)
            {
                std::string one = findStringOfSize(entry->_signals, 2);
                std::string seven = findStringOfSize(entry->_signals, 3);
                std::string four = findStringOfSize(entry->_signals, 4);
                std::string eight = findStringOfSize(entry->_signals, 7);
                std::list<std::string> zeroSixNine = findStringsOfSize(entry->_signals, 6);
                std::string nine = findSignalContainingSignal(zeroSixNine, four);
                std::list<std::string> zeroSix = removeSignal(zeroSixNine, nine);
                std::string zero = findSignalContainingSignal(zeroSix, one);
                std::string six = removeSignal(zeroSix, zero).front();
                std::list<std::string> twoThreeFive = findStringsOfSize(entry->_signals, 5);
                std::string three = findSignalContainingSignal(twoThreeFive, one);
                std::list<std::string> twoFive = removeSignal(twoThreeFive, three);
                std::string two = findSignalContaining(twoFive, findMissingChar(eight, nine));
                std::string five = removeSignal(twoFive, two).front();
                int sum = 0;
                for (size_t i = 0; i < 4; ++i)
                {
                    sum *= 10;
                    sum += matchValue(entry->_outputs[i], zero, one, two, three, four, five, six, seven, eight, nine);
                }
                total += sum;
            }

            std::stringstream result;
            result << total;

            return result.str();
        }
    }
}