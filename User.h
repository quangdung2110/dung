#ifndef USER_H
#define USER_H

#include <iostream>
#include <iomanip>
#include "Account.cpp"
#include "Information.cpp"
#include <filesystem>
#include "User.h"
#include <fstream>

extern std::string F_USER_TRANSACTION_HISTORY, F_TRANSACTION_LOG; //F_USER_TRANSACTION_HISTORY, F_TRANSACTION_LOG
namespace fs = std::filesystem;

class User : public Information {
private:
    Account account;
public:
    User();
    User(Information &i, Account j);

    Account &get_account();

    void set_account(Account _account, bool is_tmp = 0);
    
    void set_information(Information _information, bool is_tmp = 0);

    int transfer_money(std::string &ID_B, std::string &amount);

};

#endif
