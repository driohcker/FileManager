#include "FileSystem.h"
#include <iostream>
#include <sstream>
#include <chrono>
using namespace std;

/*
 * �ļ�ϵͳ��Ĺ��캯��
 * InitTest���������ڷ��㴫���ʼ���������ڲ���
 */
FileSystem::FileSystem() : currentDirectory(nullptr) {
    InitTest();
}

/*
 * �ú�������ʵ�������û�
 */
void FileSystem::addUser(const string& username) {
    if (users.find(username) != users.end()) {
        cout << "User " << username << " already exists." << endl;
    }
    else {
        users[username] = make_shared<User>(username);
        cout << "User " << username << " added successfully." << endl;
    }
}

/*
 * �ú�������ʵ�ֶԴ������û����е�¼����
 */
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

/*
 * �ú���ʵ�����û��ĵǳ�����
 */
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

/*
 * �ú���ʵ���˸��ĵ�ǰĿ¼��Ŀ��Ŀ¼
 */
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

/*
 * �ú�������ʵ�ִ���Ŀ¼
 */
void FileSystem::createDirectory(const string& dirname) {
    if (currentDirectory->subdirectories.find(dirname) == currentDirectory->subdirectories.end()) {
        currentDirectory->subdirectories[dirname] = make_shared<Directory>(dirname, currentDirectory);
        cout << "Directory " << dirname << " created successfully." << endl;
    }
    else {
        cout << "Directory " << dirname << " already exists." << endl;
    }
}

/*
 * �ú�������ʵ�ֻ�ȡ��ǰĿ¼��·��
 */
string FileSystem::getCurrentPath() const {
    string path;
    shared_ptr<Directory> dir = currentDirectory;
    while (dir) {
        path = "/" + dir->getname() + path;
        dir = (dir->parent != nullptr) ? shared_ptr<Directory>(dir->parent) : nullptr;
    }
    return path.empty() ? "/" : path;
}

/*
 * �ú������ڶԴ����·����ַ����ʶ��
 * ��ʹ��ǰĿ¼ָ�����·����ַ
 */
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
            if (it != dir->subdirectories.end()) {//Ѱ����Ŀ¼
                dir = it->second; //���ĵ���Ŀ¼
            }
            else {
                return nullptr; 
            }
        }
        
    }
    return dir;
}

/*
 * �ú�������ʵ����ʾ��ǰĿ¼�µ������ļ���Ŀ¼
 */
void FileSystem::printDirectoryTree(const shared_ptr<Directory>& dir, const string& prefix) {
    cout << prefix << dir->getname() << "/" << endl;
    for (const auto& entry : dir->subdirectories) {
        printDirectoryTree(entry.second, prefix + "    |");
    }
    for (const auto& file : dir->files) {
        cout << prefix << "    ������ " << file.first << endl;
    }
}

/*
 * �ú������ڴ�ӡ��ǰ�û��������ļ���Ŀ¼
 */
void FileSystem::printUserDirectoryTree(const string& username) {
    auto userIt = users.find(username);
    if (userIt != users.end()) {
        printDirectoryTree(userIt->second->rootDirectory, "");
    }
    else {
        cout << "User " << username << " not found." << endl;
    }
}

/*
 * �ļ�ϵͳ��Ĺ��캯��
 * �����ڷ��㴫���ʼ���������ڲ���
 */
void FileSystem::InitTest() {
    
    string username = "user1";
    
        auto user = make_shared<User>(username);
        users[username] = user;

        // Ϊÿ���û�����һЩĿ¼���ļ�
        auto docsDir = make_shared<Directory>("docs", user->rootDirectory);
        auto picsDir = make_shared<Directory>("pictures", user->rootDirectory);
        user->rootDirectory->subdirectories["docs"] = docsDir;
        user->rootDirectory->subdirectories["pictures"] = picsDir;

        // �� docs Ŀ¼�д����ļ�
        auto file1 = make_shared<File>("file1.txt", username, "rw");
        auto file2 = make_shared<File>("file2.txt", username, "rw");
        docsDir->files["file1.txt"] = file1;
        docsDir->files["file2.txt"] = file2;

        // �� pictures Ŀ¼�д���ͼƬ�ļ�
        auto pic1 = make_shared<File>("pic1.jpg", username, "rw");
        picsDir->files["pic1.jpg"] = pic1;
}
