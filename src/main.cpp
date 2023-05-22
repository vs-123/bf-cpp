#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

#include "bf.h"

using namespace std;



string readFile(const string& filename) {
    ifstream sourceCodeFile(filename);
    if (!sourceCodeFile.is_open()) {
        throw std::runtime_error("[Error]\nUnable to open file");
    }

    string sourceCode((istreambuf_iterator<char>(sourceCodeFile)), istreambuf_iterator<char>());
    sourceCodeFile.close();
    return sourceCode;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "[Usage]\n" << argv[0] << " [source_file]";
        return 1;
    }

    try {
        string sourceCode = readFile(argv[1]);
        vector<Command> commands = parse(sourceCode);
        interpret(commands);
    } catch (const std::runtime_error& e) {
        cout << e.what();
        return 1;
    }

    return 0;
}