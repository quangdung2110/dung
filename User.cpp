#include "User.h"


// bool valid_money(std::string money) {
//     for(char &c : money) {
//         if(!std::isdigit(c)) return false;
//     }
//     return true;
// }
namespace fs = std::filesystem;
std::string F_USER_TRANSACTION_HISTORY = "data/user_transaction_history/",
            F_TRANSACTION_LOG = "data/transaction_log.txt";

User::User() {}
User::User(Information &i, Account j) {
    Information::set_ID();
    set_account(j);
    set_information(i);
}

Account &User::get_account() {
    return this->account; 
}

void User::set_account(Account _account, bool is_tmp) {
    this->account = _account;
    if(!is_tmp) {
         // chưa thêm toán tư = cho account
        std::ofstream of(F_PASSWORD + account.get_user_name() + ".txt");
        of << bcrypt::generateHash(account.get_password());
        of.close();
        // chưa xử lý ghi file lỗi
    }
}   


void User::set_information(Information _information, bool is_tmp) {
    this->full_name = _information.get_full_name();
    this->address = _information.get_address();
    this->country = _information.get_country();
    this->phone_number = _information.get_phone_number();
    this->age = _information.get_age();
    this->gender = _information.get_gender();

    if(!is_tmp) {
        std::ofstream outfile(F_INFORMATION + this->account.get_user_name() + ".txt");
        outfile << static_cast<Information&>(*this);
        outfile.close();
    }
}


int User::transfer_money(std::string &ID_B, std::string &amount) {
    auto valid_money = [&](std::string &money) -> bool {
        for (char &c : money) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    };
    std::string ID_A = this->get_ID();
    std::string wallet_a = F_POINTS + ID_A + ".txt";
    std::string wallet_b = F_POINTS + ID_B + ".txt";

    if (!fs::exists(wallet_b) || (ID_A == ID_B)) {
        return 1;
    }

    std::string temp_wallet_a = wallet_a + ".tmp";
    std::string temp_wallet_b = wallet_b + ".tmp";
    std::ofstream outfile_a(temp_wallet_a);
    std::ofstream outfile_b(temp_wallet_b);
    std::ifstream infile_a(wallet_a);
    std::ifstream infile_b(wallet_b);

    if (!infile_a || !infile_b || !outfile_a || !outfile_b) {
        
        return 2;
    }

    unsigned long long balance_a, balance_b, amount_valid = 0;
    infile_a >> balance_a;
    infile_b >> balance_b;
    infile_a.close();
    infile_b.close();

    if (valid_money(amount)) {
        for (char &c : amount) {
            amount_valid = amount_valid * 10ULL + 1ULL * (c - '0');
        }
    } else {
        
        return 3;
    }

    if (balance_a < amount_valid) {
        
        return 4;
    } else {
        int last_noti = gotp::verify_otp(12);
        if (last_noti != 7) {
            
            return last_noti;
        }
    }

    balance_a -= amount_valid;
    balance_b += amount_valid;

    outfile_a << balance_a;
    outfile_a.flush();
    if (!outfile_a.good()) {
        Cloud::restore(temp_wallet_a);
        return 8;
    }

    outfile_b << balance_b;
    outfile_b.flush();
    if (!outfile_b.good()) {
        Cloud::restore(temp_wallet_b);
        return 8;
        
    }

    outfile_a.close();
    outfile_b.close();


    std::time_t now = std::time(nullptr);
    struct std::tm *tm_info = std::localtime(&now);
    char transaction_buffer[30];
    std::strftime(transaction_buffer, sizeof(transaction_buffer), "%Y-%m-%d_%H-%M-%S", tm_info); // Format time

    std::ofstream update_a(F_USER_TRANSACTION_HISTORY + ID_A + ".txt", std::ios::app);
    std::ofstream update_b(F_USER_TRANSACTION_HISTORY + ID_B + ".txt", std::ios::app);
    std::ofstream update_transaction_log(F_TRANSACTION_LOG, std::ios::app);

    if (update_transaction_log.is_open()) {


        update_transaction_log << std::string(transaction_buffer)
                            << " Transfer from " << (ID_A)
                            << " to " << (ID_B)
                            << " with amount: " << amount_valid
                            << '\n';

        update_transaction_log.flush();
        update_transaction_log.close();
    } else {
        
        Cloud::restore(F_TRANSACTION_LOG);
        return 8;
    }

    update_a << std::setw(35) << std::left << std::string(transaction_buffer)              // Căn lề trái, độ rộng 35 cho ngày giao dịch
            << std::setw(40) << std::left << (ID_A + " transferred to " + ID_B) // Căn lề trái, độ rộng 40 cho chuỗi "ID_A transferred to ID_B"
            << std::setw(10) << std::right << amount_valid                     // Căn lề phải, độ rộng 10 cho số tiền giao dịch
            << std::endl;
    update_b << std::setw(35) << std::left << std::string(transaction_buffer)              // Căn lề trái, độ rộng 35 cho ngày giao dịch
            << std::setw(40) << std::left << (ID_B + " received from " + ID_A) // Căn lề trái, độ rộng 40 cho chuỗi "ID_A transferred to ID_B"
            << std::setw(10) << std::right << amount_valid                     // Căn lề phải, độ rộng 10 cho số tiền giao dịch
            << std::endl;     


    update_a.flush();
    if (!update_a.good()) {
        
        Cloud::restore(F_USER_TRANSACTION_HISTORY + ID_A + ".txt");
        return 8;
    }

    update_b.flush();
    if (!update_b.good()) {
        
        Cloud::restore(F_USER_TRANSACTION_HISTORY + ID_B + ".txt");
        return 8;
    }
    update_a.close();
    update_b.close();

    try {
        fs::rename(temp_wallet_a, wallet_a);
    } catch (const std::exception &e) {
        
        Cloud::restore(wallet_a);
        return 8;
    }
    try {
        fs::rename(temp_wallet_b, wallet_b);
    } catch (const std::exception &e) {
        
        Cloud::restore(wallet_b);
        return 8;
    }

    return 7;
}


