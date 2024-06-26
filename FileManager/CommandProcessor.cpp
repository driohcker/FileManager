#include "CommandProcessor.h"
#include "File.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

/*
 * �������Ĺ��캯��
 * �����ļ�����ϵͳ���󷽱�ִ������
 */
CommandProcessor::CommandProcessor(FileSystem& filesystem)
    : filesystem(filesystem) {}

/*
 * �ú�������ʵ�ַ������������
 *
 */
vector<string> CommandProcessor::splitCommand(const string& command) {
    istringstream iss(command);
    vector<string> parts;
    string part;
    while (iss >> quoted(part)) {
        parts.push_back(part);
    }
    return parts;
}

/*
 * �ú������ڶ�������������ִ��
 * ���������������ָ��ʱ�����뽨����ʾ
 */
void CommandProcessor::execute(const string& command) {
    vector<string> parts = splitCommand(command);
    if (parts.empty()) return;

    const string& cmd = parts[0];
    if (cmd == "newuser") {
        if (parts.size() == 2) {
            filesystem.addUser(parts[1]);
        }
        else {
            cout << "error: create_user <username>" << endl;
        }
    }
    else if (cmd == "login") {
        if (parts.size() == 2) {
            filesystem.login(parts[1]);
            cout << "Welcome!" << parts[1] << endl;
        }
        else {
            cout << "error: login <username>" << endl;
        }
    }
    else if (cmd == "logout") {
        filesystem.logout();
    }
    else if (cmd == "newfile") {
        if (parts.size() == 3) {
            createFile(parts[1], parts[2]);
        }
        else {
            cout << "error: create_file <filename> <permissions>" << endl;
        }
    }
    else if (cmd == "open") {
        if (parts.size() == 2) {
            openFile(parts[1]);
        }
        else {
            cout << "error: open_file <filename>" << endl;
        }
    }
    else if (cmd == "close") {
        if (parts.size() == 2) {
            closeFile(parts[1]);
        }
        else {
            cout << "error: close_file <filename>" << endl;
        }
    }
    else if (cmd == "delete") {
        if (parts.size() == 2) {
            deleteFile(parts[1]);
        }
        else {
            cout << "error: delete_file <filename>" << endl;
        }
    }
    else if (cmd == "read") {
        if (parts.size() == 2) {
            readFile(parts[1]);
        }
        else {
            cout << "error: read_file <filename>" << endl;
        }
    }
    else if (cmd == "write") {
        if (parts.size() >= 3) {
            string content = command.substr(command.find(parts[1]) + parts[1].length() + 1);
            writeFile(parts[1], content);
        }
        else {
            cout << "error: write_file <filename> <content>" << endl;
        }
    }
    else if (cmd == "copy") {
        if (parts.size() == 3) {
            copyFile(parts[1], parts[2]);
        }
        else {
            cout << "error: copy_file <srcFilename/srcFilePath> <destFilename/destFilePath>" << endl;
        }
    }
    else if (cmd == "list") {
        listDirectory();
    }
    else if (cmd == "cd") {
        if (parts.size() == 2) {
            changeDirectory(parts[1]);
        }
        else {
            cout << "error: cd <path>" << endl;
        }
    }
    else if (cmd == "mkdir") {
        if (parts.size() == 2) {
            createDirectory(parts[1]);
        }
        else {
            cout << "error: mkdir <dirname>" << endl;
        }
    }
    else if (cmd == "listAll") {
        if (parts.size() == 1) {
            printAllDirectory();
        }
    }
    else if (cmd == "help") {
        helpList();
    }
    else {
        cout << "Unknown command.Please type \"help\" for more information" << endl;
    }
}

/*
 * �ú������ڴ����ļ�������Ϊ�ļ�����Ȩ��
 *
 */
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

/*
 * �ú�������ʵ�ִ��ļ�
 *
 */
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

/*
 * �ú�������ʵ�ֹر��ļ�
 *
 */
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

/*
 * �ú�������ʵ��ɾ���ļ�
 *
 */
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

/*
 * �ú�������ʵ�ֶ�ȡ�ļ�
 *
 */
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

/*
 * �ú�������ʵ���޸��ļ�
 *
 */
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

/*
 * �ú�������ʵ�ָ����ļ�
 *
 */
void CommandProcessor::copyFile(const string& srcPath, const string& destDirPath) {
    if (filesystem.currentUser) {
        // ����Դ�ļ�·��
        auto srcDir = filesystem.navigateToDirectory(srcPath.substr(0, srcPath.find_last_of('/')));
        string srcFilename = srcPath.substr(srcPath.find_last_of('/') + 1);

        // ���Դ�ļ��Ƿ����
        if (srcDir && srcDir->files.find(srcFilename) != srcDir->files.end()) {
            auto srcFile = srcDir->files[srcFilename];

            // ����Ŀ��Ŀ¼·��
            auto destDir = filesystem.navigateToDirectory(destDirPath);
            if (destDir) {
                // ��Ŀ��Ŀ¼�д����ļ�����
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

/*
 * �ú�������ʵ��չʾ��ǰĿ¼�������ļ�
 *
 */
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

/*
 * �ú�������ʵ�ָ��ĵ�ǰĿ¼��ָ��Ŀ¼
 */
void CommandProcessor::changeDirectory(const string& path) {
    filesystem.changeDirectory(path);
}

/*
 * �ú�������ʵ�ִ���Ŀ¼
 */
void CommandProcessor::createDirectory(const string& dirname) {
    filesystem.createDirectory(dirname);
}

/*
 * �ú�������ʵ����ʾ��ǰ�û��������ļ�
 */
void CommandProcessor::printAllDirectory() {
    filesystem.printUserDirectoryTree(filesystem.currentUser->getUsername());
}

/*
 * �ú�������ʵ��help�嵥��ʵ��
 */
void CommandProcessor::helpList() {
    cout << setw(15) << left << "newuser" << left << setw(61) << "newuser <username>" << left << setw(50) << "---create a user to use file system" << endl;
    cout << setw(15) << left << "login" << left << setw(61) << "login <username>" << left << setw(50) << "---login user account which has been created" << endl;
    cout << setw(15) << left << "logout" << left << setw(61) << "logout" << left << setw(50) << "---logout a user account which is logined" << endl;
    cout << setw(15) << left << "newfile" << left << setw(61) << "newfile <filename> <permissions(read/write/execute)>" << left << setw(50) << "---create a file and define its permission" << endl;
    cout << setw(15) << left << "open" << left << setw(61) << "open <filename>" << left << setw(50) << "---open a file if it has been created" << endl;
    cout << setw(15) << left << "close" << left << setw(61) << "close <filename>" << left << setw(50) << "---close open file" << endl;
    cout << setw(15) << left << "delete" << left << setw(61) << "delete <filename>" << left << setw(50) << "---delete a created file" << endl;
    cout << setw(15) << left << "read" << left << setw(61) << "read <filename>" << left << setw(50) << "---just read this file" << endl;
    cout << setw(15) << left << "write" << left << setw(61) << "write <filename> <content>" << left << setw(50) << "---write a few of contents to a file" << endl;
    cout << setw(15) << left << "copy" << left << setw(61) << "copy <sourcefilename> <tagetfilename>" << left << setw(50) << "---copy a file to another file" << endl;
    cout << setw(15) << left << "list" << left << setw(61) << "list" << left << setw(50) <<"---show current file list" << endl;
    cout << setw(15) << left << "listAll" << left << setw(61) << "listAll" << left << setw(50) << "---show all file list" << endl;
    cout << setw(15) << left << "cd" << left << setw(61) << "cd <dirpath>" << left << setw(50) << "---open a directory" << endl;
    cout << setw(15) << left << "mkdir" << left << setw(61) << "mkdir <dirname>" << left << setw(50) << "---create a directory" << endl;
    cout << setw(15) << left << "" << setw(30) << "" << endl;
}
