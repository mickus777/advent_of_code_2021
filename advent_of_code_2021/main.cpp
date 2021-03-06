
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
    case 6:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day6_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day6_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 7:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day7_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day7_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 8:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day8_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day8_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 9:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day9_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day9_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 10:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day10_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day10_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 11:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day11_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day11_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 12:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day12_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day12_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 13:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day13_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day13_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 14:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day14_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day14_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 15:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day15_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day15_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 16:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day16_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day16_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 17:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day17_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day17_2(inputFile, verbose);
        default:
            return "Not known yet!";
        }
    case 18:
        switch (part)
        {
        case 1:
            return mbk::advent_of_code_2021::day18_1(inputFile, verbose);
        case 2:
            return mbk::advent_of_code_2021::day18_2(inputFile, verbose);
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