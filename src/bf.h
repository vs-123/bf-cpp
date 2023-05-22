#ifndef BF_H
#define BF_H

#include <vector>
#include <iostream>
#include <string>

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
    Command(CommandType type, std::size_t index) : type(type), index(index) {} // This one for LoopOpen and LoopClose
};

std::ostream& operator<<(std::ostream& output, const Command& cmd);

std::vector<Command> parse(std::string source);

void interpret(std::vector<Command> commands);

#endif