#include "FileSystem.h"
#include <iostream>
#include <sstream>

using namespace std;

FileSystem::FileSystem() : currentDirectory(nullptr) {
    InitTest();
}

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
        currentDirectory = currentUser->rootDirectory;
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
        currentDirectory = nullptr;
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void FileSystem::changeDirectory(const string& path) {
    auto newDirectory = navigateToDirectory(path);
    if (newDirectory) {
        currentDirectory = newDirectory;
        cout << "Changed directory to " << getCurrentPath() << endl;
    }
    else {
        cout << "Directory not found: " << path << endl;
    }
}

void FileSystem::createDirectory(const string& dirname) {
    if (currentDirectory->subdirectories.find(dirname) == currentDirectory->subdirectories.end()) {
        currentDirectory->subdirectories[dirname] = make_shared<Directory>(dirname, currentDirectory);
        cout << "Directory " << dirname << " created successfully." << endl;
    }
    else {
        cout << "Directory " << dirname << " already exists." << endl;
    }
}

string FileSystem::getCurrentPath() const {
    string path;
    shared_ptr<Directory> dir = currentDirectory;
    while (dir) {
        path = "/" + dir->name + path;
        dir = (dir->parent != nullptr) ? shared_ptr<Directory>(dir->parent) : nullptr;
    }
    return path.empty() ? "/" : path;
}

shared_ptr<Directory> FileSystem::navigateToDirectory(const string& path) const {
    istringstream iss(path);
    string token;
    shared_ptr<Directory> dir = nullptr;
    dir = (path[0] == '/') ? currentUser->rootDirectory : currentDirectory;

    while (getline(iss, token, '/')) {
        if (token == "..") {
            dir = dir->parent;
        }
        else if (token != "." && !token.empty()) {
            auto it = dir->subdirectories.find(token);
            if (it != dir->subdirectories.end()) {//寻找子目录
                dir = it->second; //更改到该目录
            }
            else {
                return nullptr; 
            }
        }
        
    }
    return dir;
}

void FileSystem::printDirectoryTree(const shared_ptr<Directory>& dir, const string& prefix) {
    cout << prefix << dir->name << "/" << endl;
    for (const auto& entry : dir->subdirectories) {
        printDirectoryTree(entry.second, prefix + "    |");
    }
    for (const auto& file : dir->files) {
        cout << prefix << "    └── " << file.first << endl;
    }
}

void FileSystem::printUserDirectoryTree(const string& username) {
    auto userIt = users.find(username);
    if (userIt != users.end()) {
        printDirectoryTree(userIt->second->rootDirectory, "");
    }
    else {
        cout << "User " << username << " not found." << endl;
    }
}

void FileSystem::InitTest() {
    
    string username = "user1";
    
        auto user = make_shared<User>(username);
        users[username] = user;

        // 为每个用户创建一些目录和文件
        auto docsDir = make_shared<Directory>("docs", user->rootDirectory);
        auto picsDir = make_shared<Directory>("pictures", user->rootDirectory);
        user->rootDirectory->subdirectories["docs"] = docsDir;
        user->rootDirectory->subdirectories["pictures"] = picsDir;

        // 在 docs 目录中创建文件
        auto file1 = make_shared<File>("file1.txt", username, "rw");
        auto file2 = make_shared<File>("file2.txt", username, "rw");
        docsDir->files["file1.txt"] = file1;
        docsDir->files["file2.txt"] = file2;

        // 在 pictures 目录中创建图片文件
        auto pic1 = make_shared<File>("pic1.jpg", username, "rw");
        picsDir->files["pic1.jpg"] = pic1;
}
