#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "CommandProcessor.h"

using namespace std;

bool eula() {
    string input;
    
    while (true) {
        cout << "Do you agree EULA(y/n)?" << endl;
        string input;
        getline(cin,input);
        if (input == "y")
            return true;
        else if (input == "n")
            return false;
        else continue;
    }
    
}

void visualLoad() {
    cout << "Initializing filesystem" << endl;
    int _time = 0;
    int random = 0;
    
    srand(static_cast<unsigned int>(time(nullptr)));

    while (_time < 100) {
        random = rand() % 10;
        _time += random;
        if (_time > 100) _time = 100;
        Sleep(random * 100);
        cout << "Initializing process:" << _time << "%" << endl;
    }
    cout << "Filesystem initialize finished." << endl;
    Sleep(2000);
    cout << "Loading users'data" << endl;

    _time = 0;
    random = 0;
    while (_time < 100) {
        random = rand() % 10 + 10;
        _time += random;
        if (_time > 100) _time = 100;
        Sleep(random * 100);
        cout << "Loading process:" << _time << "%" << endl;
    }
    cout << "Users'data loaded." << endl;
}

/*
 * 该类是测试类
 */
int main() {
    //visualLoad();

    FileSystem fs;
    CommandProcessor cp(fs);

    string command;
    //bool isStart = eula();
    //Sleep(2000);

    while (true) {
        cout << fs.getCurrentPath() << " > ";
        getline(cin, command);
        if (command == "exit") break;
        cp.execute(command);
    }
    return 0;
}

