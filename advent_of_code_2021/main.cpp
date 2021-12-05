
#include "days.h"

#include <iostream>
#include <string>

std::string compute(int day, int part, const std::string inputFile, bool verbose)
{
    switch (day)
    {
    case 1:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day1_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day1_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 2:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day2_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day2_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 3:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day3_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day3_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 4:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day4_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day4_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 5:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day5_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day5_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    default:
        return "Not know yet!";
    }
}

int main(int argc, char** argv)
{
    if (argc < 4)
        return 1;

    int day = std::stoi(argv[1]);
    int part = std::stoi(argv[2]);
    std::string inputFile = argv[3];

    bool verbose = false;
    if (argc > 4)
        if (argv[4] == std::string("v"))
            verbose = true;

    std::cout << "Day " << day << " part " << part << ": " << compute(day, part, inputFile, verbose) << std::endl;

    return 0;
}