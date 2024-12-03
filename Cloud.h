#ifndef CLOUD_H
#define CLOUD_H

#include <string>
#include <cstdlib>
#include <sstream>
namespace Cloud {
    void backup();
    void restore(std::string position);
    bool is_tracked(std::string position);
}

#endif // ACCOUNT_H
