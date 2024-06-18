#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <unordered_map>
#include <memory>
#include "User.h"
#include "Directory.h"

using namespace std;

class FileSystem {
public:
    unordered_map<string, shared_ptr<User>> users;
    shared_ptr<User> currentUser;
    shared_ptr<Directory> currentDirectory;

    FileSystem();

    void addUser(const string& username);
    void login(const string& username);
    void logout();
    void changeDirectory(const string& path);
    void createDirectory(const string& dirname);
    string getCurrentPath() const;
    shared_ptr<Directory> navigateToDirectory(const string& path) const;
    void printDirectoryTree(const shared_ptr<Directory>& dir, const string& prefix);
    void printUserDirectoryTree(const string& username);
    void InitTest();
};

#endif // FILESYSTEM_H
