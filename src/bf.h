#ifndef BF_H
#define BF_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum class CommandType {
    Increment,
    Decrement,
    MoveLeft,
    MoveRight,
    LoopOpen,
    LoopClose,
    PrintCell,
    InputCell,
};

std::ostream& operator<<(std::ostream& output, const CommandType& cmdType);

struct Command {
    CommandType type;
    size_t index;

    Command(CommandType type) : type(type), index(0) {}
    Command(CommandType type, size_t index) : type(type), index(index) {} // This one for LoopOpen and LoopClose
};

std::ostream& operator<<(std::ostream& output, const Command& cmd);

vector<Command> parse(string source);

void interpret(vector<Command> commands);

#endif