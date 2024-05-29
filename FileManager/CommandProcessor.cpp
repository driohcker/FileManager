#include "CommandProcessor.h"
#include "FileSystem.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

CommandProcessor::CommandProcessor(FileSystem& filesystem) 
    : filesystem(filesystem) {}

void CommandProcessor::execute(const string& command) {
    vector<string> parts = splitCommand(command);
    if (parts.empty()) return;

    const string& cmd = parts[0];
    if (cmd == "create_user") {
        if (parts.size() == 2)
            filesystem.addUser(parts[1]);
        else
            cout << "error: create_user <username>" << endl;
    }
    else if (cmd == "login") {
        if(parts.size() == 2)
            filesystem.login(parts[1]);
        else
            cout << "error: login <username>" << endl;
    }
    else if (cmd == "logout") {
        filesystem.logout();
    }
    else if (cmd == "create_file") {
        if(parts.size() == 3)
            createFile(parts[1], parts[2]);
        else
            cout << "error: create_file <filename> <permissions>" << endl;
    }
    else if (cmd == "open_file") {
        if(parts.size() == 2)
            openFile(parts[1]);
        else
            cout << "error: open_file <filename>" << endl;
    }
    else if (cmd == "close_file") {
        if (parts.size() == 2)
            closeFile(parts[1]);
        else
            cout << "error: close_file <filename>" << endl;
    }
    else if (cmd == "delete_file") {
        if (parts.size() == 2)
            deleteFile(parts[1]);
        else
            cout << "error: delete_file <filename>" << endl;
    }
    else if (cmd == "read_file") {
        if (parts.size() == 2)
            readFile(parts[1]);
        else
            cout << "error: read_file <filename>" << endl;
    }
    else if (cmd == "write_file") {
        if (parts.size() == 3)
            writeFile(parts[1], parts[2]);
        else
            cout << "error: write_file <filename> <content>" << endl;
    }
    else if (cmd == "copy_file") {
        if (parts.size() == 3)
            copyFile(parts[1], parts[2]);
        else
            cout << "error: copy_file <sourcefilename> <tagetfilename>" << endl;
    }
    else if (cmd == "list_dir") {
        listDirectory();
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
        auto currentDirectory = filesystem.currentUser->rootDirectory;
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
        auto currentDirectory = filesystem.currentUser->rootDirectory;
        if (currentDirectory->files.find(filename) != currentDirectory->files.end()) {
            currentDirectory->files[filename]->isOpen = true;
            cout << "File " << filename << " is now open." << endl;
        } else {
            cout << "File " << filename << " does not exist." << endl;
        }
    } else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::closeFile(const string& filename) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentUser->rootDirectory;
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
        auto currentDirectory = filesystem.currentUser->rootDirectory;
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
        auto currentDirectory = filesystem.currentUser->rootDirectory;
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
        auto currentDirectory = filesystem.currentUser->rootDirectory;
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

void CommandProcessor::copyFile(const string& srcFilename, const string& destFilename) {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentUser->rootDirectory;
        if (currentDirectory->files.find(srcFilename) != currentDirectory->files.end()) {
            auto srcFile = currentDirectory->files[srcFilename];
            auto newFile = make_shared<File>(destFilename, srcFile->owner, "rwx");
            newFile->content = srcFile->content;
            currentDirectory->files[destFilename] = newFile;
            cout << "File " << srcFilename << " copied to " << destFilename << " successfully." << endl;
        }
        else {
            cout << "Source file " << srcFilename << " does not exist." << endl;
        }
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

void CommandProcessor::listDirectory() {
    if (filesystem.currentUser) {
        auto currentDirectory = filesystem.currentUser->rootDirectory;
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

void CommandProcessor::helpList() {
    cout << setw(15) << left << "create_user"   << left << setw(61) << "create_user <username>"                                     << left << setw(50) << "---create a user to use file system"            << endl;
    cout << setw(15) << left << "login"         << left << setw(61) << "login <username>"                                           << left << setw(50) << "---login user account which has been created"   << endl;
    cout << setw(15) << left << "logout"        << left << setw(61) << "logout"                                                     << left << setw(50) << "---logout a user account which is logined"      << endl;
    cout << setw(15) << left << "create_file"   << left << setw(61) << "create_file <filename> <permissions(read/write/execute)>"   << left << setw(50) << "---create a file and define its permission"     << endl;
    cout << setw(15) << left << "open_file"     << left << setw(61) << "open_file <filename>"                                       << left << setw(50) << "---open a file if it has been created"          << endl;
    cout << setw(15) << left << "close_file"    << left << setw(61) << "close_file <filename>"                                      << left << setw(50) << "---close open file"                             << endl;
    cout << setw(15) << left << "delete_file"   << left << setw(61) << "delete_file <filename>"                                     << left << setw(50) << "---delete a created file"                       << endl;
    cout << setw(15) << left << "read_file"     << left << setw(61) << "read_file <filename>"                                       << left << setw(50) << "---just read this file"                         << endl;
    cout << setw(15) << left << "write_file"    << left << setw(61) << "write_file <filename> <content>"                            << left << setw(50) << "---write a few of contents to a file"           << endl;
    cout << setw(15) << left << "copy_file"     << left << setw(61) << "copy_file <sourcefilename> <tagetfilename>"                 << left << setw(50) << "---copy a file to another file"                 << endl;
    cout << setw(15) << left << "list_dir"      << left << setw(61) << "list_dir" << "---show current file list"                    << left << setw(50) << endl;
    cout << setw(15) << left << "" << setw(30) << "" << endl;
}

vector<string> CommandProcessor::splitCommand(const string& command) {
    istringstream iss(command);
    vector<string> parts;
    string part;
    while (iss >> part) {
        parts.push_back(part);
    }
    return parts;
}