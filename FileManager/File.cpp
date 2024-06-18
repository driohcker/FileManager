#include "File.h"
using namespace std;


File::File(const string& name, const string& owner, const string& permissions) 
    : name(name), owner(owner), content(""), isOpen(false) {
    this->permissions["read"] = permissions.find('r') != string::npos;
    this->permissions["write"] = permissions.find('w') != string::npos;
    this->permissions["execute"] = permissions.find('x') != string::npos;
}



