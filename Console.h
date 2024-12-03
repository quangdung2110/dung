#ifndef CONSOLE_H
#define CONSOLE_H

#include<iostream>
#include "User.cpp"
#include <filesystem>
#include <string>


class Console {
private:
    const std::string un_manager = "lede", pw_manager = "lede6666";
    User cur;
public:
    Console();

    void reset();

    void print(int x, int y, std::string s);

    std::string otp(int x, int y);

    std::string input(int x, int y, bool is_plus, bool is_password, int mn);

    std::string change(std::string& title, std::string& enter_new, std::string& old_ans, bool age, bool gender, bool phone_number);

    bool create_account();

    void change_information(bool manager);

    void print_information();

    void transfer_money();

    void transaction_history();

    void list_of_users();

    void log_in_useraccount();
    
    void view_list_of_users_account();

    void create_user_account();

    bool create_password();

    void system_transaction_history();

    void user_operation(bool manager);

    void manager_opertion();

    void Start_The_Program();    

};

#endif
