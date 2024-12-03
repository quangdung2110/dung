#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Menu.h"

void Menu::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;    // col
    coord.Y = y;    // row
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menu::print_login_frame() {
    system("cls");
    std::string s = R"(
                                        _________________________________________
                                       |                                         |
                                       |           WELCOME TO OUR BANK           |
                                       |              PLEASE LOGIN!              |
                                       |_________________________________________|
                                       |                                         | 
                                       | Enter username:                         |
                                       |_________________________________________|
                                       |                                         |  
                                       | Enter password:                         |
                                       |_________________________________________|    
                                       |                                         |
                                       | Note that pressing the 'Tab' will exit  |
                                       |_________________________________________|
                                                   Press '+' to create an account                                       
    )";
    std::cout << s;
}

void Menu::print_change_information() {
    system("cls");
    std::string s = R"(
                                        ________________________________________
                                       |                                        |
                                       |           CHANGE INFORMATION           |
                                       |________________________________________|
                                       |                                        |
                                       | 1. Fullname                            |
                                       |________________________________________|
                                       |                                        |    
                                       | 2. Password                            |
                                       |________________________________________|
                                       |                                        |
                                       | 3. Address                             |
                                       |________________________________________|
                                       |                                        |
                                       | 4. Age                                 |
                                       |________________________________________|
                                       |                                        |
                                       | 5. Gender                              |
                                       |________________________________________|
                                       |                                        |
                                       | 6. Phone Number                        |
                                       |________________________________________|
                                       |                                        |
                                       | 7. Country                             |
                                       |________________________________________|
                                       |                                        |
                                       | Note that pressing the 'Tab' will exit |
                                       |________________________________________|)";
    std::cout << s;
}

void Menu::print_user_menu() {
    system("cls");
    std::string str = R"(
                                        ________________________________________
                                       |                                        |
                                       |           USER'S BANKING MENU          |
                                       |________________________________________|
                                       |                                        |
                                       | 1. Change Information                  |
                                       |________________________________________|
                                       |                                        |
                                       | 2. Check Information                   |
                                       |________________________________________|
                                       |                                        |
                                       | 3. Transfer Money                      |
                                       |________________________________________|
                                       |                                        |
                                       | 4. Check Transaction History           |
                                       |________________________________________|
                                       |                                        |
                                       | Note that pressing the 'Tab' will exit |
                                       |________________________________________|)"    ;
    std::cout << str;
}

void Menu::print_manager_menu() {
    system("cls");
    std::string str = R"(
                                        ________________________________________
                                       |                                        |
                                       |         MANAGER'S BANKING MENU         |
                                       |________________________________________|
                                       |                                        |
                                       | 1. List of Users                       |
                                       |________________________________________|
                                       |                                        |
                                       | 2. Create User Account                 |
                                       |________________________________________|
                                       |                                        |
                                       | 3. System Transaction History          |
                                       |________________________________________|
                                       |                                        |
                                       | Note that pressing the 'Tab' will exit |
                                       |________________________________________|)"  ;
    std::cout << str;
}

void Menu::notification(std::string s, int x, int y) {
    system("cls");
    std::cout << R"(
                             _____________________________________________________________
                            |                                                             |
                            |                    O~~~NOTIFICATION~~~O                     |
                            |                                                             |
                            |                                                             |
                            |                                                             |
                            |_____________________________________________________________|)";
    
    gotoxy(x, y);
    std::cout << s;
    gotoxy(5, 15);
    Sleep(3000);
}

void Menu::create_account_screen() {
    system("cls");
    std::string s = R"(
                    _________________________________________________________________________________
                   |                                                                                 |
                   |                      CREATE AN ACCOUNT FOR THE LOGIN USER                       |
                   |_________________________________________________________________________________|
                   |                                        |                                        |
                   | Enter Username:                        | Enter Fullname:                        |                              
                   |________________________________________|________________________________________|
                   |                                        |                                        |
                   | Enter Password:                        | Enter Age:                             |                         
                   |________________________________________|________________________________________|
                   |                                        |                                        |
                   | Enter Password Again:                  | Enter Gender (Male : 1, Female : 0)    |
                   |________________________________________|________________________________________|
                   |                                        |                                        |
                   | Enter Phone Number:                    | Enter Address:                         |
                   |________________________________________|________________________________________|
                   |                                        |                                        |
                   | Note that pressing the 'Tab' will back | Enter Country:                         |
                   |________________________________________|________________________________________|)";                          
    std::cout << s;                                          
}

void Menu::create_account_for_user_screen() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |     CREATE AN ACCOUNT FOR THE USER     |
                                       |________________________________________|
                                       |                                        |
                                       | 1. Enter User Name:                    |
                                       |________________________________________|
                                       |                                        |
                                       | 2. Enter Full Name:                    |
                                       |________________________________________|
                                       |                                        |
                                       | 3. Enter Age:                          |
                                       |________________________________________|
                                       |                                        |
                                       | 4. Enter Gender (Male : 1, Female : 0) |
                                       |________________________________________|
                                       |                                        |
                                       | 5. Enter Phone Number:                 |
                                       |________________________________________|
                                       |                                        |
                                       | 6. Enter Address:                      |
                                       |________________________________________|
                                       |                                        |
                                       | 7. Enter Country:                      |
                                       |________________________________________|
                                       |                                        |
                                       | Note that pressing the 'Tab' will back |
                                       |________________________________________|)";
}

void Menu::print_otp() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       | --> CHANGE:                            |
                                       |________________________________________|
                                       |                                        |
                                       | Enter new                              |
                                       |________________________________________|
                                       |                                        |
                                       |          OTP:                          |
                                       |   __________________________________   |                           
                                       |  |                                  |  |  
                                       |  | __   __   __   __   __   __   __ |  |     
                                       |  |__________________________________|  | 
                                       |________________________________________|                                       
                                       |                                        |
                                       | Note that pressing the 'Tab' will back |
                                       |________________________________________|)";
}

void Menu::identification_information() {    
    system("cls");
    std::string str = R"(
    IDENTIFICATION INFORMATION
    --------------------------------------------------------------------------------------
    
    Full Name:                              
    Age:          
    Gender:
    

    ACCOUNT INFORMATION
    --------------------------------------------------------------------------------------
    Account Balance:
    Phone Number:
    Country:
    
    --------------------------------------------------------------------------------------
                             Note that pressing the 'Tab' will back    
)";
    std::cout << str;
}

void Menu::transfer_money_screen(){
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |             TRANSFER MONEY             |
                                       |________________________________________|
                                       |                                        |
                                       | Enter Amount:                          |
                                       |________________________________________|
                                       |                                        |
                                       | Enter ID:                              |
                                       |________________________________________|
                                       |                                        |
                                       |          OTP:                          |
                                       |   __________________________________   |
                                       |  |                                  |  |
                                       |  | __   __   __   __   __   __   __ |  |
                                       |  |__________________________________|  |
                                       |________________________________________|
                                       |                                        |
                                       | Note that pressing the 'Tab' will back |
                                       |________________________________________|
    )";
}

void Menu::print_transaction_history() {
    system("cls");
    std::string str = R"(
    TRANSACTION HISTORY     
    -------------------                                                      Note that pressing the 'Tab' will back
    _______________________________________________________________________________________________________________
                                                                                                                  
    DATE OF IMPLEMENTATION               TRANSACTION                                  AMOUNT    
    _______________________________________________________________________________________________________________

)";
    std::cout << str;
}

void Menu::print_list_of_users_main() {
    system("cls");
    std::string s = R"(
                                        ________________________________________
                                       |                                        |
                                       |              LIST OF USERS             |
                                       |________________________________________|
                                       |                                        | 
                                       | 1. Log In To The User's Account        |
                                       |________________________________________|
                                       |                                        |  
                                       | 2. View List of Users                  |
                                       |________________________________________|    
                                       |                                        |
                                       | Note that pressing the 'Tab' will back |
                                       |________________________________________|)";
    std::cout << s;
}

void Menu::print_log_in_user_account() {
    system("cls");
    std::string s = R"(
                                        ________________________________________
                                       |                                        |  
                                       | Enter the username to search for:      |
                                       |________________________________________|    
                                       |                                        |
                                       | Note that pressing the 'Tab' will back |
                                       |________________________________________|)";
    std::cout << s;    
}

void Menu::print_list_of_user() {
    system("cls");
    std::cout << R"(
    LIST OF USERS
    ------------                                                             Note that pressing the 'Tab' will back
    _______________________________________________________________________________________________________________

    ID WALLET            FULL NAME          PHONE NUMBER         POINTS        ADDRESS            COUNTRY
    _______________________________________________________________________________________________________________

    )";
}

void Menu::system_transaction_history_screen(){
    system("cls");
    std::cout << R"(                                              
    SYSTEM TRANSACTION HISTORY
    --------------------------                                               Note that pressing the 'Tab' will back
    _______________________________________________________________________________________________________________

         TRANSACTION TIME                                 TRANSACTION
    _______________________________________________________________________________________________________________

    )";
}

void Menu::print_create_password() {
    system("cls");
    std::string s = R"(
                                        ________________________________________
                                       |                                        |  
                                       |            CREATE PASSWORD             |
                                       |________________________________________|    
                                       |                                        |
                                       | Enter password                         |
                                       |________________________________________|
                                       |                                        |  
                                       | Enter password again                   |
                                       |________________________________________|    
                                       |                                        |
                                       | Note that pressing the 'Tab' will back |
                                       |________________________________________|)";
    std::cout << s;    
}