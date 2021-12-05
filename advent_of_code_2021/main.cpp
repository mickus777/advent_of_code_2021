
#include "days.h"

#include <iostream>
#include <string>

std::string compute(int day, const std::string inputFile, bool verbose)
{
    switch (day)
    {
    case 1:
        return mbk::advent_of_code_2021::day1(inputFile, verbose);
    default:
        return "Not know yet!";
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
        return 1;

    int day = std::stoi(argv[1]);
    std::string inputFile = argv[2];

    bool verbose = false;
    if (argc > 3)
        if (argv[3] == std::string("v"))
            verbose = true;

    std::cout << "Day " << day << ": " << compute(day, inputFile, verbose) << std::endl;

    return 0;
}