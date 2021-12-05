
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace mbk
{
    namespace advent_of_code_2021
    {
        enum Command { Forward, Up, Down, End };

        Command toCommand(const std::string& text)
        {
            if (text == "forward")
                return Command::Forward;
            else if (text == "up")
                return Command::Up;
            else if (text == "down")
                return Command::Down;
            else
                return Command::End;
        }
        std::string toString(const Command& command)
        {
            switch (command)
            {
            case Command::Forward: return "forward";
            case Command::Up: return "up";
            case Command::Down: return "down";
            case Command::End: 
            default:
                return "end";
            }
        }

        struct CommandData
        {
            CommandData(Command command, int distance = 0) : _command(command), _distance(distance) {}

            Command _command;
            int _distance;
        };

        class CommandParser
        {
        public:
            CommandParser(std::ifstream& input)
                : _input(input)
            {}

            CommandData getNext()
            {
                if (_input.peek() == EOF)
                    return CommandData(Command::End);

                std::string row;
                std::getline(_input, row);

                size_t spacePosition = row.find(' ');
                return CommandData(toCommand(row.substr(0, spacePosition)), std::stoi(row.substr(spacePosition + 1)));
            }

        private:
            std::ifstream& _input;
        };

        std::string day2_1(const std::string& input, bool verbose = false)
        {
            int position = 0;
            int depth = 0;

            std::ifstream stream(input);
            CommandParser commandParser(stream);

            for (CommandData command = commandParser.getNext(); command._command != Command::End; command = commandParser.getNext())
            {
                switch (command._command)
                {
                case Command::Forward:
                    position += command._distance;
                    break;
                case Command::Up:
                    depth -= command._distance;
                    break;
                case Command::Down:
                    depth += command._distance;
                    break;
                case Command::End:
                default:
                    break;
                }

                if (verbose)
                    std::cout << toString(command._command) << " " << command._distance << " -> " << position << "," << depth << std::endl;
            }

            std::stringstream result;
            result << position * depth;

            return result.str();
        }

        std::string day2_2(const std::string& input, bool verbose = false)
        {
            int aim = 0;
            int position = 0;
            int depth = 0;

            std::ifstream stream(input);
            CommandParser commandParser(stream);

            for (CommandData command = commandParser.getNext(); command._command != Command::End; command = commandParser.getNext())
            {
                switch (command._command)
                {
                case Command::Forward:
                    position += command._distance;
                    depth += command._distance * aim;
                    break;
                case Command::Up:
                    aim -= command._distance;
                    break;
                case Command::Down:
                    aim += command._distance;
                    break;
                case Command::End:
                default:
                    break;
                }

                if (verbose)
                    std::cout << toString(command._command) << " " << command._distance << " -> " << position << "," << depth << std::endl;
            }

            std::stringstream result;
            result << position * depth;

            return result.str();
        }
    }
}