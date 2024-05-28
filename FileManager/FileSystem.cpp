#include "FileSystem.h"
#include <iostream>
using namespace std;

void FileSystem::addUser(const string& username) {
    if (users.find(username) != users.end()) {
        cout << "User " << username << " already exists." << endl;
    }
    else {
        users[username] = make_shared<User>(username);
        cout << "User " << username << " added successfully." << endl;
    }
}

void FileSystem::login(const string& username) {
    if (users.find(username) != users.end()) {
        currentUser = users[username];
        cout << "User " << username << " logged in successfully." << endl;
    }
    else {
        cout << "User " << username << " does not exist." << endl;
    }
}

void FileSystem::logout() {
    if (currentUser) {
        cout << "User " << currentUser->username << " logged out." << endl;
        currentUser = nullptr;
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}
