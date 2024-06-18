#include "Directory.h"

using namespace std;

Directory::Directory(const string& name, shared_ptr<Directory> parent)
    : name(name), parent(parent) {}
