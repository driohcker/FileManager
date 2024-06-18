#include <iostream>
#include <string>
#include "CommandProcessor.h"

using namespace std;

int main() {
    FileSystem fs;
    CommandProcessor cp(fs);

    string command;
    
    while (true) {
        cout << fs.getCurrentPath() << " > ";
        getline(cin, command);
        if (command == "exit") break;
        cp.execute(command);
    }

    return 0;
}
