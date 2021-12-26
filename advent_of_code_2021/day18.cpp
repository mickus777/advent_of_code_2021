
#include "fileutilities.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mbk
{
    namespace advent_of_code_2021
    {
        struct Node
        {
            Node() : _left(0), _right(0), _lvalue(0), _rvalue(0) {}
            ~Node()
            {
                if (_left != 0)
                    delete _left;
                if (_right != 0)
                    delete _right;
            }

            Node* _left;
            Node* _right;
            int _lvalue;
            int _rvalue;
        };

        Node* parse(const std::string& text, size_t& position)
        {
            if (text[position] != '[')
                throw 0;
            ++position;

            Node* node = new Node();

            if (text[position] == '[')
                node->_left = parse(text, position);
            else
            {
                size_t nextPosition = text.find_first_of(',', position);
                node->_lvalue = std::stoi(text.substr(position, nextPosition - position));
                position = nextPosition;
            }

            ++position;

            if (text[position] == '[')
                node->_right = parse(text, position);
            else
            {
                size_t nextPosition = text.find_first_of(']', position);
                node->_rvalue = std::stoi(text.substr(position, nextPosition - position));
                position = nextPosition;
            }

            if (text[position] != ']')
                throw 0;
            ++position;

            return node;
        }

        void print(Node* node)
        {
            std::cout << "[";

            if (node->_left != 0)
                print(node->_left);
            else
                std::cout << node->_lvalue;

            std::cout << ",";

            if (node->_right != 0)
                print(node->_right);
            else
                std::cout << node->_rvalue;

            std::cout << "]";
        }

        void pushLeft(Node* node, int value)
        {
            if (node->_left != 0)
                pushLeft(node->_left, value);
            else
                node->_lvalue += value;
        }

        void pushRight(Node* node, int value)
        {
            if (node->_right != 0)
                pushRight(node->_right, value);
            else
                node->_rvalue += value;
        }

        std::pair<int, int> explode(Node* node, size_t depth)
        {
            if (node->_left != 0)
            {
                if (depth == 3)
                {
                    Node* l = node->_left;
                    node->_left = 0;
                    node->_lvalue = 0;
                    if (node->_right != 0)
                        pushLeft(node->_right, l->_rvalue);
                    else
                        node->_rvalue += l->_rvalue;
                    return std::pair<int, int>(l->_lvalue, 0);
                }
                else
                {
                    std::pair<int, int> result = explode(node->_left, depth + 1);
                    if (result.first != -1)
                    {
                        if (result.first > 0)
                            return result;
                        else
                        {
                            if (node->_right != 0)
                                pushLeft(node->_right, result.second);
                            else
                                node->_rvalue += result.second;
                            return std::pair<int, int>(0, 0);
                        }
                    }
                }
            }
            if (node->_right != 0)
            {
                if (depth == 3)
                {
                    Node* r = node->_right;
                    node->_right = 0;
                    node->_rvalue = 0;
                    if (node->_left != 0)
                        pushRight(node->_left, r->_lvalue);
                    else
                        node->_lvalue += r->_lvalue;
                    return std::pair<int, int>(0, r->_rvalue);
                }
                else
                {
                    std::pair<int, int> result = explode(node->_right, depth + 1);
                    if (result.first != -1)
                    {
                        if (result.first > 0)
                        {
                            if (node->_left != 0)
                                pushRight(node->_left, result.first);
                            else
                                node->_lvalue += result.first;
                            return std::pair<int, int>(0, 0);
                        }
                        else
                        {
                            return result;
                        }
                    }
                }
            }

            return std::pair<int, int>(-1, -1);
        }

        Node* splitValue(int value)
        {
            Node* n = new Node();
            n->_lvalue = value / 2;
            n->_rvalue = value - n->_lvalue;
            return n;
        }

        bool split(Node* node)
        {
            if (node->_left != 0)
            {
                if (split(node->_left))
                    return true;
            }
            else
            {
                if (node->_lvalue > 9)
                {
                    node->_left = splitValue(node->_lvalue);
                    return true;
                }
            }

            if (node->_right != 0)
            {
                if (split(node->_right))
                    return true;
            }
            else
            {
                if (node->_rvalue > 9)
                {
                    node->_right = splitValue(node->_rvalue);
                    return true;
                }
            }

            return false;
        }

        void reduce(Node* node)
        {
            while (true)
            {
                std::pair<int, int> explodeResult = explode(node, 0);
                if (explodeResult.first >= 0 && explodeResult.second >= 0)
                    continue;

                if (split(node))
                    continue;

                break;
            }
        }

        int magnitude(Node* node)
        {
            int lvalue = 0;
            if (node->_left != 0)
                lvalue = 3 * magnitude(node->_left);
            else
                lvalue = 3 * node->_lvalue;

            int rvalue = 0;
            if (node->_right != 0)
                rvalue = 2 * magnitude(node->_right);
            else
                rvalue = 2 * node->_rvalue;

            return lvalue + rvalue;
        }

        Node* add(Node* n1, Node* n2)
        {
            Node* sum = new Node();
            sum->_left = n1;
            sum->_right = n2;
            return sum;
        }

        Node* copy(Node* node)
        {
            Node* n = new Node();
            if (node->_left != 0)
                n->_left = copy(node->_left);
            else
                n->_lvalue = node->_lvalue;
            if (node->_right != 0)
                n->_right = copy(node->_right);
            else
                n->_rvalue = node->_rvalue;
            return n;
        }

        void printNode(Node* node)
        {
            print(node);
            std::cout << std::endl;
        }

        Node* parseLine(const std::string& line)
        {
            size_t position = 0;
            return parse(line, position);
        }

        std::string day18_1(const std::string& input, bool verbose)
        {
            std::list<std::string> lines = file_utilities::readLines(input);
            auto line = lines.begin();

            Node* sum = parseLine(*line);
            ++line;

            while (line != lines.end())
            {
                if (verbose)
                    printNode(sum);

                Node* nextValue = parseLine(*line);
                ++line;

                sum = add(sum, nextValue);
                reduce(sum);
            }

            if (verbose)
                printNode(sum);

            std::stringstream result;
            result << magnitude(sum);

            return result.str();
        }

        std::string day18_2(const std::string& input, bool verbose)
        {
            std::list<std::string> lines = file_utilities::readLines(input);
            auto line = lines.begin();

            std::vector<Node*> nodes(lines.size(), 0);
            for (size_t i = 0; i < lines.size(); ++i)
            {
                nodes[i] = parseLine(*line);
                ++line;
            }

            int greatestMagnitude = 0;
            for (size_t i = 0; i < nodes.size(); ++i)
            {
                for (size_t j = 0; j < nodes.size(); ++j)
                {
                    if (i == j)
                        continue;

                    Node* n1 = copy(nodes[i]);
                    Node* sum = add(n1, copy(nodes[j]));
                    reduce(sum);
                    int m = magnitude(sum);
                    if (m > greatestMagnitude)
                    {
                        if (verbose)
                        {
                            printNode(nodes[i]);
                            printNode(nodes[j]);
                            printNode(sum);
                            std::cout << m << std::endl;
                        }

                        greatestMagnitude = m;
                    }
                }
            }

            std::stringstream result;
            result << greatestMagnitude;

            return result.str();
        }
    }
}
