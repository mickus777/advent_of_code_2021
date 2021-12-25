
#include "fileutilities.h"

#include <iostream>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        std::string toBinary(char ch)
        {
            switch (ch)
            {
            case '0': return "0000";
            case '1': return "0001";
            case '2': return "0010";
            case '3': return "0011";
            case '4': return "0100";
            case '5': return "0101";
            case '6': return "0110";
            case '7': return "0111";
            case '8': return "1000";
            case '9': return "1001";
            case 'A': return "1010";
            case 'B': return "1011";
            case 'C': return "1100";
            case 'D': return "1101";
            case 'E': return "1110";
            case 'F': return "1111";
            default: throw 0;
            }
        }

        std::string toBinary(const std::string& hexadecimal)
        {
            std::stringstream stream;

            for (auto ch = hexadecimal.begin(); ch != hexadecimal.end(); ++ch)
                stream << toBinary(*ch);

            return stream.str();
        }

        long long toDecimal(char ch)
        {
            switch (ch)
            {
            case '0': return 0;
            case '1': return 1;
            default: throw 0;
            }
        }

        long long toDecimal(const std::string& binary)
        {
            long long decimal = 0;

            for (size_t i = 0; i < binary.size(); ++i)
            {
                decimal = decimal * 2;
                decimal += toDecimal(binary[i]);
            }

            return decimal;
        }

        struct Package
        {
            long long _version;
            long long _type;
            long long _value;
            long long _lengthType;
            std::list<Package*> _subPackages;
        };

        long long parseValue(const std::string& binaryProgram, size_t& position)
        {
            std::stringstream binaryValue;

            bool oneMore = true;
            while (oneMore)
            {
                oneMore = toDecimal(binaryProgram.substr(position, 1));
                position += 1;

                binaryValue << binaryProgram.substr(position, 4);
                position += 4;
            }

            return toDecimal(binaryValue.str());
        }

        Package* parse(const std::string& binaryProgram, size_t& position)
        {
            Package* package = new Package();

            package->_version = toDecimal(binaryProgram.substr(position, 3));
            position += 3;
            package->_type = toDecimal(binaryProgram.substr(position, 3));
            position += 3;

            if (package->_type == 4)
            {
                package->_value = parseValue(binaryProgram, position);
            }
            else
            {
                package->_lengthType = toDecimal(binaryProgram.substr(position, 1));
                position += 1;

                if (package->_lengthType == 0)
                {
                    long long bitLength = toDecimal(binaryProgram.substr(position, 15));
                    position += 15;

                    long long packageEnd = position + bitLength;
                    while (position < packageEnd)
                        package->_subPackages.push_back(parse(binaryProgram, position));
                }
                if (package->_lengthType == 1)
                {
                    long long subPackages = toDecimal(binaryProgram.substr(position, 11));
                    position += 11;

                    for (long long i = 0; i < subPackages; ++i)
                        package->_subPackages.push_back(parse(binaryProgram, position));
                }
            }

            return package;
        }

        long long sumVersions(Package* package)
        {
            long long sum = package->_version;

            for (auto it = package->_subPackages.begin(); it != package->_subPackages.end(); ++it)
                sum += sumVersions(*it);

            return sum;
        }

        long long evaluate(Package* package, bool verbose)
        {
            long long value = 0;

            auto it = package->_subPackages.begin();
            switch (package->_type)
            {
            case 0:
                if (verbose)
                    std::cout << "(";
                for (auto it = package->_subPackages.begin(); it != package->_subPackages.end(); ++it)
                {
                    if (verbose && it != package->_subPackages.begin())
                        std::cout << "+";
                    value += evaluate(*it, verbose);
                }
                if (verbose)
                    std::cout << ")";
                break;
            case 1:
                if (verbose)
                    std::cout << "(";
                value = 1;
                for (auto it = package->_subPackages.begin(); it != package->_subPackages.end(); ++it)
                {
                    if (verbose && it != package->_subPackages.begin())
                        std::cout << "*";
                    value *= evaluate(*it, verbose);
                }
                if (verbose)
                    std::cout << ")";
                break;
            case 2:
                if (verbose)
                    std::cout << "min(";
                value = LLONG_MAX;
                for (auto it = package->_subPackages.begin(); it != package->_subPackages.end(); ++it)
                {
                    if (verbose && it != package->_subPackages.begin())
                        std::cout << ",";
                    long long subValue = evaluate(*it, verbose);
                    if (subValue < value)
                        value = subValue;
                }
                if (verbose)
                    std::cout << ")";
                break;
            case 3:
                if (verbose)
                    std::cout << "max(";
                for (auto it = package->_subPackages.begin(); it != package->_subPackages.end(); ++it)
                {
                    if (verbose && it != package->_subPackages.begin())
                        std::cout << ",";
                    long long subValue = evaluate(*it, verbose);
                    if (subValue > value)
                        value = subValue;
                }
                ,
                if (verbose)
                    std::cout << ")";
                break;
            case 4:
                if (verbose)
                    std::cout << package->_value;
                value = package->_value;
                break;
            case 5:
            {
                if (verbose)
                    std::cout << "(";
                long long firstValue = evaluate(*it, verbose);
                if (verbose)
                    std::cout << ">";
                ++it;
                long long secondValue = evaluate(*it, verbose);
                if (verbose)
                    std::cout << ")";
                value = (firstValue > secondValue ? 1 : 0);
            }
                break;
            case 6:
            {
                if (verbose)
                    std::cout << "(";
                long long firstValue = evaluate(*it, verbose);
                if (verbose)
                    std::cout << "<";
                ++it;
                long long secondValue = evaluate(*it, verbose);
                if (verbose)
                    std::cout << ")";
                value = (firstValue < secondValue ? 1 : 0);
            }
                break;
            case 7:
            {
                if (verbose)
                    std::cout << "(";
                long long firstValue = evaluate(*it, verbose);
                if (verbose)
                    std::cout << "==";
                ++it;
                long long secondValue = evaluate(*it, verbose);
                if (verbose)
                    std::cout << ")";
                value = (firstValue == secondValue ? 1 : 0);
            }
                break;
            default: throw 0;
            }

            return value;
        }

        Package* parse(const std::string& input, bool verbose)
        {
            std::string hexadecimalProgram = file_utilities::readLines(input).front();
            std::string binaryProgram = toBinary(hexadecimalProgram);

            if (verbose)
            {
                std::cout << hexadecimalProgram << std::endl;
                std::cout << binaryProgram << std::endl;
            }

            size_t position = 0;
            return parse(binaryProgram, position);
        }

        std::string day16_1(const std::string& input, bool verbose)
        {
            Package* package = parse(input, verbose);

            std::stringstream result;
            result << sumVersions(package);

            return result.str();
        }

        std::string day16_2(const std::string& input, bool verbose)
        {
            Package* package = parse(input, verbose);

            std::stringstream result;
            result << evaluate(package, verbose);
            if (verbose)
                std::cout << std::endl;

            return result.str();
        }
    }
}
