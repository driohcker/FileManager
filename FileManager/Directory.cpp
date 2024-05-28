#include "Directory.h"
using namespace std;

Directory::Directory(const string& name, Directory* parent)
    : name(name), parent(parent) {}
