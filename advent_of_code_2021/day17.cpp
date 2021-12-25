
#include "fileutilities.h"

#include <iostream>
#include <list>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        bool doesHit(int lowerX, int upperX, int lowerY, int upperY, int velocityX, int velocityY)
        {
            int positionX = 0;
            int positionY = 0;
            while (positionX <= upperX && positionY >= lowerY)
            {
                if (positionX >= lowerX && positionY <= upperY)
                    return true;

                positionX += velocityX;
                positionY += velocityY;
                if (velocityX > 0)
                    --velocityX;
                --velocityY;
            }

            return false;
        }

        std::list<std::pair<int, int>> findHits(int lowerX, int upperX, int lowerY, int upperY, int velocityX)
        {
            std::list<std::pair<int, int>> hits;

            for (int velocityY = -1000; velocityY < 1000; ++velocityY)
                if (doesHit(lowerX, upperX, lowerY, upperY, velocityX, velocityY))
                    hits.push_back(std::pair<int, int>(velocityX, velocityY));

            return hits;
        }

        std::list<std::pair<int, int>> findHits(int lowerX, int upperX, int lowerY, int upperY)
        {
            std::list<std::pair<int, int>> hits;

            for (int velocityX = 0; velocityX <= upperX; ++velocityX)
            {
                std::list<std::pair<int, int>> moreHits = findHits(lowerX, upperX, lowerY, upperY, velocityX);
                hits.insert(hits.begin(), moreHits.begin(), moreHits.end());
            }

            return hits;
        }

        std::list<std::pair<int, int>> day17(const std::string& input, bool verbose)
        {
            std::string definition = file_utilities::readLines(input).front();

            int lowerX = 0;
            int upperX = 0;
            int lowerY = 0;
            int upperY = 0;
            {
                std::string coordinates = definition.substr(13);

                size_t pos = coordinates.find_first_of("..");
                lowerX = std::stoi(coordinates.substr(2, pos - 2));

                size_t nextPos = coordinates.find_first_of(',', pos);
                upperX = std::stoi(coordinates.substr(pos + 2, nextPos - pos - 2));

                pos = nextPos + 4;
                nextPos = coordinates.find_first_of("..", pos);
                lowerY = std::stoi(coordinates.substr(pos, nextPos - pos));

                upperY = std::stoi(coordinates.substr(nextPos + 2));
            }
            if (verbose)
                std::cout << "X: " << lowerX << ".." << upperX << ", Y: " << lowerY << ".." << upperY << std::endl;

            return findHits(lowerX, upperX, lowerY, upperY);
        }

        std::string day17_1(const std::string& input, bool verbose)
        {
            std::list<std::pair<int, int>> hits = day17(input, verbose);

            int greatestY = 0;
            for (auto hit = hits.begin(); hit != hits.end(); ++hit)
                if (hit->second > greatestY)
                    greatestY = hit->second;

            int height = 0;
            for (int speed = 0; speed <= greatestY; ++speed)
                height += speed;

            std::stringstream result;
            result << height;

            return result.str();
        }

        std::string day17_2(const std::string& input, bool verbose)
        {
            std::stringstream result;
            result << day17(input, verbose).size();

            return result.str();
        }
    }
}