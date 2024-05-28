#include <iostream>
#include "File.cpp"
#include "CommandProcessor.cpp"
using namespace std;

int main() {
    FileSystem fs;
    CommandProcessor cp(fs);

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        if (command == "exit") break;
        cp.execute(command);
    }

    return 0;
}
