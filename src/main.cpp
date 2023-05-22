#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

#include "bf.h"

std::string readFile(const std::string& filename) {
    std::ifstream sourceCodeFile(filename);
    if (!sourceCodeFile.is_open()) {
        throw std::runtime_error("[Error]\nUnable to open file");
    }

    std::string sourceCode((std::istreambuf_iterator<char>(sourceCodeFile)), std::istreambuf_iterator<char>());
    sourceCodeFile.close();
    return sourceCode;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "[Usage]\n" << argv[0] << " [source_file]";
        return 1;
    }

    try {
        std::string sourceCode = readFile(argv[1]);
        std::vector<Command> commands = parse(sourceCode);
        interpret(commands);
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
        return 1;
    }

    return 0;
}