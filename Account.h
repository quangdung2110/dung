#ifndef ACCOUNT_H
#define ACCOUNT_H


#include <iostream>
#include <bitset>
#include <string>

extern std::string F_PASSWORD;

class Account {
private:
    std::string user_name, password;

public:
    Account();
    Account(std::string _user_name, std::string _password);

    std::string get_user_name();
    std::string get_password();
    bool valid_password(const std::string &_password);
    bool set_password(const std::string &_password, bool is_auto = 0);
    bool is_auto_password(std::string full_name, int age, int gender);
    void set_user_name(const std::string &_user_name);
    void operator = (Account &other);
};

#endif // ACCOUNT_H
