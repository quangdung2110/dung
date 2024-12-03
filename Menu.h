#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>


namespace Menu {
	// thêm mấy cái frontend vào đây còn mấy cái xử lý đăng nhập là làm ở main
    // Hàm gotoxy n?m ngoài l?p LoginScreen
    void gotoxy(int x, int y);
    void print_login_frame();
    void print_change_information();
    void print_user_menu();
    void print_manager_menu();
    void notification(std::string s, int x, int y);
    void create_account_screen();
    void create_account_for_user_screen();
    void print_create_password();
    void print_otp();
    void identification_information();
    void transfer_money_screen();
    void print_transaction_history();
    void print_list_of_user();
    void print_list_of_users_main();
    void print_log_in_user_account();
    void system_transaction_history_screen();
    void print_password_user();
}

#endif