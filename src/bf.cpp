#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <limits>

#include "bf.h"

const size_t MEMORY_SIZE = 30000;

std::ostream& operator<<(std::ostream& output, const CommandType& cmdType) {
    switch(cmdType) {
        case CommandType::Increment:
            output << "Increment";
            break;
        case CommandType::Decrement:
            output << "Decrement";
            break;
        case CommandType::MoveLeft:
            output << "MoveLeft";
            break;
        case CommandType::MoveRight:
            output << "MoveRight";
            break;
        case CommandType::LoopOpen:
            output << "LoopOpen";
            break;
        case CommandType::LoopClose:
            output << "LoopClose";
            break;
        case CommandType::PrintCell:
            output << "PrintCell";
            break;
        case CommandType::InputCell:
            output << "InputCell";
            break;
        default:
            output << "Unknown CommandType";
    }
    return output;
}

std::ostream& operator<<(std::ostream& output, const Command& cmd) {
    output << "Command { type: " << cmd.type << ", index: " << cmd.index << " }";
    return output;
}

std::vector<Command> parse(std::string source) {
    std::vector<Command> output;
    std::vector<std::size_t> loopStack;

    for (char character : source) {
        switch (character) {
            case '+':{
            output.push_back(Command(CommandType::Increment));
            }break;

            case '-':{
            output.push_back(Command(CommandType::Decrement));
            }break;

            case '<':{
            output.push_back(Command(CommandType::MoveLeft));
            }break;

            case '>':{
            output.push_back(Command(CommandType::MoveRight));
            }break;

            case '[':{
            size_t loopStart = output.size();
            output.push_back(Command(CommandType::LoopOpen, loopStart));
            loopStack.push_back(loopStart);
            }break;

            case ']':{
            if (loopStack.size() < 1) {
                std::cout << "[Error at command index " << output.size() << "]";
                std::cout << "Unmatched ']'\n";
                exit(1);
            }
            size_t loopStart = loopStack.back();
            output[loopStart] = Command(CommandType::LoopOpen, output.size());
            output.push_back(Command(CommandType::LoopClose, loopStart));
            }break;

            case '.':{
            output.push_back(Command(CommandType::PrintCell));
            }break;

            case ',':{
            output.push_back(Command(CommandType::InputCell));
            }break;

            default:
            break;
        }
    }

    return output;
}

void interpret(std::vector<Command> commands) {
    std::uint8_t memory[MEMORY_SIZE];
    std::size_t pointer = 0;
    std::size_t commandIndex = 0;

    while (commandIndex < commands.size()) {
        Command command = commands[commandIndex];

        switch (command.type) {
            case CommandType::Increment:{
                if (memory[pointer] < std::numeric_limits<uint8_t>::max()) memory[pointer]++;
            }break;

            case CommandType::Decrement:{
                if (memory[pointer] > std::numeric_limits<uint8_t>::min()) memory[pointer]--;
            }break;

            case CommandType::MoveRight:{
                if (pointer < MEMORY_SIZE - 1) pointer++;
            }break;

            case CommandType::MoveLeft:{
                if (pointer > 0) pointer--;
            }break;

            case CommandType::PrintCell:{
                std::cout << char(memory[pointer]);
            }break;

            case CommandType::InputCell:{
                char c;
                std::cin >> c;
                memory[pointer] = size_t(c);
            }break;

            case CommandType::LoopOpen:{
                if (memory[pointer] == 0)
                    commandIndex = command.index;
            }break;

            case CommandType::LoopClose:{
                if (memory[pointer] != 0)
                    commandIndex = command.index;
            }break;

            default:{
                std::cout << "[Error]" << std::endl << command << " " << commands.size() << std::endl;
            }break;
        }

        commandIndex += 1;
    }
}