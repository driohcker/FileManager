#include "CommandProcessor.h"
#include "File.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

CommandProcessor::CommandProcessor(FileSystem& filesystem)
    : filesystem(filesystem) {}

vector<string> CommandProcessor::splitCommand(const string& command) {
    istringstream iss(command);
    vector<string> parts;
    string part;
    while (iss >> quoted(part)) {
        parts.push_back(part);
    }
    return parts;
}

void CommandProcessor::execute(const string& command) {
    vector<string> parts = splitCommand(command);
    if (parts.empty()) return;

    const string& cmd = parts[0];
    if (cmd == "create_user") {
        if (parts.size() == 2) {
            filesystem.addUser(parts[1]);
        }
        else {
            cout << "Usage: create_user <username>" << endl;
        }
    }
    else if (cmd == "login") {
        if (parts.size() == 2) {
            filesystem.login(parts[1]);
        }
        else {
            cout << "Usage: login <username>" << endl;
        }
    }
    else if (cmd == "logout") {
        filesystem.logout();
    }
    else if (cmd == "create_file") {
        if (parts.size() == 3) {
            createFile(parts[1], parts[2]);
        }
        else {
            cout << "Usage: create_file <filename> <permissions>" << endl;
        }
    }
    else if (cmd == "open_file") {
        if (parts.size() == 2) {
            openFile(parts[1]);
        }
        else {
            cout << "Usage: open_file <filename>" << endl;
        }
    }
    else if (cmd == "close_file") {
        if (parts.size() == 2) {
            closeFile(parts[1]);
        }
        else {
            cout << "Usage: close_file <filename>" << endl;
        }
    }
    else if (cmd == "delete_file") {
        if (parts.size() == 2) {
            deleteFile(parts[1]);
        }
        else {
            cout << "Usage: delete_file <filename>" << endl;
        }
    }
    else if (cmd == "read_file") {
        if (parts.size() == 2) {
            readFile(parts[1]);
        }
        else {
            cout << "Usage: read_file <filename>" << endl;
        }
    }
    else if (cmd == "write_file") {
        if (parts.size() >= 3) {
            string content = command.substr(command.find(parts[1]) + parts[1].length() + 1);
            writeFile(parts[1], content);
        }
        else {
            cout << "Usage: write_file <filename> <content>" << endl;
        }
    }
    else if (cmd == "copy_file") {
        if (parts.size() == 3) {
            copyFile(parts[1], parts[2]);
        }
        else {
            cout << "Usage: copy_file <srcFilename/srcFilePath> <destFilename/destFilePath>" << endl;
        }
    }
    else if (cmd == "list_dir") {
        listDirectory();
    }
    else if (cmd == "cd") {
        if (parts.size() == 2) {
            changeDirectory(parts[1]);
        }
        else {
            cout << "Usage: cd <path>" << endl;
        }
    }
    else if (cmd == "mkdir") {
        if (parts.size() == 2) {
            createDirectory(parts[1]);
        }
        else {
            cout << "Usage: mkdir <dirname>" << endl;
        }
    }
    else if (cmd == "prtAllDir") {
        if (parts.size() == 1) {
            printAllDirectory();
        }
    }
    else if (cmd == "help") {
        helpList();
    }
    else {
        cout << "Unknown command." << endl;
    }
}

void CommandProcessor::createFile(const string& filename, const string& permissions) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentDirectory;
        if (currentDirectory->files.find(filename) != currentDirectory->files.end()) {
            cout << "File " << filename << " already exists." << endl;
        }
        else {
            auto newFile = make_shared<File>(filename, filesystem.currentUser->username, permissions);
            currentDirectory->files[filename] = newFile;
            cout << "File " << filename << " created successfully." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::openFile(const string& filename) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentDirectory;
        if (currentDirectory->files.find(filename) != currentDirectory->files.end()) {
            currentDirectory->files[filename]->isOpen = true;
            cout << "File " << filename << " is now open." << endl;
        }
        else {
            cout << "File " << filename << " does not exist." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::closeFile(const string& filename) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentDirectory;
        if (currentDirectory->files.find(filename) != currentDirectory->files.end() && currentDirectory->files[filename]->isOpen) {
            currentDirectory->files[filename]->isOpen = false;
            cout << "File " << filename << " is now closed." << endl;
        }
        else {
            cout << "File " << filename << " does not exist or is not open." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::deleteFile(const string& filename) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentDirectory;
        if (currentDirectory->files.find(filename) != currentDirectory->files.end()) {
            currentDirectory->files.erase(filename);
            cout << "File " << filename << " deleted successfully." << endl;
        }
        else {
            cout << "File " << filename << " does not exist." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::readFile(const string& filename) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentDirectory;
        if (currentDirectory->files.find(filename) != currentDirectory->files.end()) {
            auto file = currentDirectory->files[filename];
            if (file->permissions["read"]) {
                cout << "Reading file " << filename << ": " << file->content << endl;
            }
            else {
                cout << "Read permission denied for file " << filename << "." << endl;
            }
        }
        else {
            cout << "File " << filename << " does not exist." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::writeFile(const string& filename, const string& content) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentDirectory;
        if (currentDirectory->files.find(filename) != currentDirectory->files.end()) {
            auto file = currentDirectory->files[filename];
            if (file->permissions["write"]) {
                file->content = content;
                cout << "Writing to file " << filename << " successful." << endl;
            }
            else {
                cout << "Write permission denied for file " << filename << "." << endl;
            }
        }
        else {
            cout << "File " << filename << " does not exist." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::copyFile(const string& srcPath, const string& destDirPath) {
    if (filesystem.currentUser) {
        // 解析源文件路径
        auto srcDir = filesystem.navigateToDirectory(srcPath.substr(0, srcPath.find_last_of('/')));
        string srcFilename = srcPath.substr(srcPath.find_last_of('/') + 1);

        // 检查源文件是否存在
        if (srcDir && srcDir->files.find(srcFilename) != srcDir->files.end()) {
            auto srcFile = srcDir->files[srcFilename];

            // 解析目标目录路径
            auto destDir = filesystem.navigateToDirectory(destDirPath);
            if (destDir) {
                // 在目标目录中创建文件副本
                auto newFile = make_shared<File>(srcFilename, srcFile->owner, "rwx");
                newFile->content = srcFile->content;
                destDir->files[srcFilename] = newFile;
                cout << "File " << srcPath << " copied to " << destDirPath << "/" << srcFilename << " successfully." << endl;
            }
            else {
                cout << "Destination directory " << destDirPath << " does not exist." << endl;
            }
        }
        else {
            cout << "Source file " << srcPath << " does not exist." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}



void CommandProcessor::listDirectory() {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentDirectory;
        cout << "Directory listing for " << filesystem.currentUser->username << ":" << endl;
        for (const auto& file : currentDirectory->files) {
            cout << "- " << file.first << endl;
        }
        for (const auto& dir : currentDirectory->subdirectories) {
            cout << "+ " << dir.first << "/" << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::changeDirectory(const string& path) {
    filesystem.changeDirectory(path);
}

void CommandProcessor::createDirectory(const string& dirname) {
    filesystem.createDirectory(dirname);
}

void CommandProcessor::printAllDirectory() {
    filesystem.printUserDirectoryTree(filesystem.currentUser->getUsername());
}

void CommandProcessor::helpList() {
    cout << setw(15) << left << "create_user" << left << setw(61) << "create_user <username>" << left << setw(50) << "---create a user to use file system" << endl;
    cout << setw(15) << left << "login" << left << setw(61) << "login <username>" << left << setw(50) << "---login user account which has been created" << endl;
    cout << setw(15) << left << "logout" << left << setw(61) << "logout" << left << setw(50) << "---logout a user account which is logined" << endl;
    cout << setw(15) << left << "create_file" << left << setw(61) << "create_file <filename> <permissions(read/write/execute)>" << left << setw(50) << "---create a file and define its permission" << endl;
    cout << setw(15) << left << "open_file" << left << setw(61) << "open_file <filename>" << left << setw(50) << "---open a file if it has been created" << endl;
    cout << setw(15) << left << "close_file" << left << setw(61) << "close_file <filename>" << left << setw(50) << "---close open file" << endl;
    cout << setw(15) << left << "delete_file" << left << setw(61) << "delete_file <filename>" << left << setw(50) << "---delete a created file" << endl;
    cout << setw(15) << left << "read_file" << left << setw(61) << "read_file <filename>" << left << setw(50) << "---just read this file" << endl;
    cout << setw(15) << left << "write_file" << left << setw(61) << "write_file <filename> <content>" << left << setw(50) << "---write a few of contents to a file" << endl;
    cout << setw(15) << left << "copy_file" << left << setw(61) << "copy_file <sourcefilename> <tagetfilename>" << left << setw(50) << "---copy a file to another file" << endl;
    cout << setw(15) << left << "list_dir" << left << setw(61) << "list_dir" << "---show current file list" << left << setw(50) << endl;
    cout << setw(15) << left << "cd" << left << setw(61) << "cd <dirpath>" << "---open a directory" << left << setw(50) << endl;
    cout << setw(15) << left << "mkdir" << left << setw(61) << "mkdir <dirname>" << "---create a directory" << left << setw(50) << endl;
    cout << setw(15) << left << "" << setw(30) << "" << endl;
}