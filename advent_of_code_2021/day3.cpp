
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mbk
{
    namespace advent_of_code_2021
    {
        class ReportParser
        {
        public:
            ReportParser(const std::string& input) : _input(std::ifstream(input)) {}

            std::vector<int> getNext()
            {
                if (_input.peek() == EOF)
                    return std::vector<int>();

                std::string row;
                std::getline(_input, row);

                std::vector<int> report(row.size());
                for (size_t i = 0; i < row.size(); ++i)
                    report[i] = (row.at(i) == '1' ? 1 : -1);

                return report;
            }

        private:
            std::ifstream _input;
        };

        struct ReportNode
        {
            ReportNode() : _1(0), _0(0), _count(0) {}
            ~ReportNode()
            {
                if (_1 != 0)
                    delete _1;
                if (_0 != 0)
                    delete _0;
            }

            ReportNode* _1;
            ReportNode* _0;
            int _count;
        };

        void printReport(std::vector<int>& report)
        {
            for (size_t i = 0; i < report.size(); ++i)
                std::cout << (report[i] > 0 ? "1" : "0");
        }

        std::string day3_1(const std::string& input, bool verbose = false)
        {
            ReportParser reportParser(input);

            std::vector<int> totalReport = reportParser.getNext();

            for (std::vector<int> report = reportParser.getNext(); report.size() > 0; report = reportParser.getNext())
            {
                for (size_t i = 0; i < report.size(); ++i)
                    totalReport[i] += report[i];
                if (verbose)
                {
                    printReport(report);
                    std::cout << " -> ";
                    printReport(totalReport);
                    std::cout << std::endl;
                }
            }

            int gamma = 0;
            int epsilon = 0;
            for (size_t i = 0; i < totalReport.size(); ++i)
            {
                gamma <<= 1;
                epsilon <<= 1;
                if (totalReport[i] > 0)
                    gamma += 1;
                else
                    epsilon += 1;
            }

            std::stringstream result;
            result << gamma * epsilon;

            return result.str();
        }
 
        void insert(ReportNode* node, std::vector<int>::const_iterator it, std::vector<int>::const_iterator end)
        {
            ReportNode* nextNode = 0;
            if (*it > 0)
            {
                if (node->_1 == 0)
                    node->_1 = new ReportNode();
                node->_1->_count += 1;
                nextNode = node->_1;
            }
            else
            {
                if (node->_0 == 0)
                    node->_0 = new ReportNode();
                node->_0->_count += 1;
                nextNode = node->_0;
            }
            
            ++it;

            if (it != end)
                insert(nextNode, it, end);
        }

        int calculateRating(ReportNode* node, bool selectHigh)
        {
            int rating = 0;

            while (node != 0)
            {
                int count0 = (node->_0 != 0 ? node->_0->_count : 0);
                int count1 = (node->_1 != 0 ? node->_1->_count : 0);

                if (count0 == 0 && count1 == 0)
                    break;

                rating <<= 1;
                if (count0 == 0)
                {
                    rating += 1;
                    node = node->_1;
                }
                else if (count1 == 0)
                {
                    node = node->_0;
                }
                else if (count0 > count1)
                {
                    if (selectHigh)
                    {
                        node = node->_0;
                    }
                    else
                    {
                        rating += 1;
                        node = node->_1;
                    }
                }
                else
                {
                    if (selectHigh)
                    {
                        rating += 1;
                        node = node->_1;
                    }
                    else
                    {
                        node = node->_0;
                    }
                }
            }

            return rating;
        }

        std::string day3_2(const std::string& input, bool verbose)
        {
            ReportNode reportNode;

            ReportParser reportParser(input);

            for (std::vector<int> report = reportParser.getNext(); report.size() > 0; report = reportParser.getNext())
                insert(&reportNode, report.begin(), report.end());

            int oxygenRating = calculateRating(&reportNode, true);
            int scrubberRating = calculateRating(&reportNode, false);

            std::stringstream result;
            result << oxygenRating * scrubberRating;

            return result.str();
        }
    }
}