#include "Account.h"
#include <bitset>

std::string F_PASSWORD = "data/store_password/";

Account::Account() {
    this->user_name = "";
    this->password = "";
}

// Constructor với tham số
Account::Account(std::string _user_name, std::string _password) {
    this->user_name = _user_name;
    this->password = _password;
}

// Hàm getter cho `user_name`
std::string Account::get_user_name() {
    return user_name;
}

// Hàm getter cho `password`
std::string Account::get_password() {
    return password;
}

// Kiểm tra tính hợp lệ của mật khẩu
bool Account::valid_password(const std::string &_password) {
    std::bitset<4> valid;

    for (char c : _password) {
        if (c >= 'a' && c <= 'z') valid.set(0);
        else if (c >= 'A' && c <= 'Z') valid.set(1);
        else if (c >= '0' && c <= '9') valid.set(2);
        else if (c >= char(32) && c <= char(126)) valid.set(3);
        else {
            return false;
        }
    }

    return valid.all();
}

bool Account::is_auto_password(std::string full_name, int age, int gender) {
    for(char &c : full_name) tolower(c);
    return this->password == (full_name + '&' + std::to_string(age) + '&' + std::to_string(gender));
}

// Thiết lập mật khẩu với điều kiện hợp lệ
bool Account::set_password(const std::string &_password, bool is_auto) {
    if (is_auto || valid_password(_password)) {
        this->password = _password;
        return true;
    } else {
        return false;
    }
}

// Thiết lập tên người dùng
void Account::set_user_name(const std::string &_user_name) {
    this->user_name = _user_name;
}
void Account::operator = (Account &other) {
    this->user_name = other.get_user_name();
    this->password = other.get_password();
}