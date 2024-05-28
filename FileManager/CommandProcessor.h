#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <vector>
#include "File.h"
#include "FileSystem.h"

class CommandProcessor {
public:
    FileSystem& filesystem;

    CommandProcessor(FileSystem& filesystem);
    void execute(const string& command);

private:
    void createFile(const string& filename, const string& permissions);
    void openFile(const string& filename);
    void closeFile(const string& filename);
    void deleteFile(const string& filename);
    void readFile(const string& filename);
    void writeFile(const string& filename, const string& content);
    void copyFile(const string& srcFilename, const string& destFilename);
    void listDirectory();
    void helpList();

    vector<string> splitCommand(const string& command);
};

#endif