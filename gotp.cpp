#include "gotp.h"
std::string gotp::generate_otp() {
    const std::string str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    constexpr int length_otp = 6, length_str = 62;

    std::string otp = "";
    for (int i = 0; i < length_otp; ++i) {
        otp += str[gen() % length_str];
    }
    return otp;
}

int gotp::verify_otp(int y) {
    Menu::gotoxy(56, y); //otp
    std::string OTP = gotp::generate_otp();
    std::cout << OTP;

    Menu::gotoxy(47, y + 3);
    char c;
    std::string check_otp = "";
    
    while(true) {
        c = _getch();
        
        if(c == 9) return 6;
        
        else if(check_otp.size() == 6 && c != 8) {
            if(c == 13) break;
            continue;
        }
        else if(c == 13) continue;
        else if(c == 8) {
            if(!check_otp.empty()) {
                check_otp.pop_back();
                Menu::gotoxy(48 + check_otp.size()*5 - 1, y + 3);
                std::cout << " ";
                Menu::gotoxy(48 + check_otp.size()*5 - 1, y + 3);
            }
        }
        else {
            check_otp.push_back(c);
            std::cout << c;
            if(check_otp.size() == 6)
                Menu::gotoxy(48 + check_otp.size()*5 + 1 -5, y + 3);
            else
                Menu::gotoxy(48 + check_otp.size()*5 - 1, y + 3);
        }
    }
    return OTP == check_otp ? 7 : 5;
}
