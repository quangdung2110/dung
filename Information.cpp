#include "Information.h"


std::string F_INFORMATION = "data/store_information/", F_POINTS = "data/store_wallet/";
std::string file_path1 = "data/store_wallet/total_wallet.txt";

Information::Information() {
    this->full_name = this->address = this->country = this->ID = this->phone_number = "";
    this->age = this->balance = 0;
    this->gender = -1;
}

// Getter functions
std::string Information::get_full_name() const { return this->full_name; }
std::string Information::get_address() const { return this->address; }
std::string Information::get_country() const { return this->country; }
std::string Information::get_phone_number() const { return this->phone_number; }
int Information::get_age() const { return this->age; }
bool Information::get_gender() const { return this->gender; }
std::string Information::get_ID() const { return this->ID; }
unsigned long long Information::get_balance() const {return this->balance;}

// Setter functions
void Information::set_balance(unsigned long long _balance) {
    this->balance = _balance;
}
void Information::set_ID(std::string _ID) { 
    if(!_ID.empty()) {
        this->ID = _ID;
    } else {
        auto generate_ID = [&]() -> std::string {
            std::string res = "";
            std::uniform_int_distribution<int> uni(1, 9999);
            for (int i = 0; i < 3; i++) {
                int tmp = uni(gotp::gen);
                std::string s = std::to_string(tmp);
                res += std::string(4 - s.size(), '0') + s;
            }
            return res;
        };
        auto generate_balance = [&]()->unsigned long long {
            std::uniform_int_distribution<unsigned short> uni(0, 65535);
            return uni(gotp::gen);
        };
        std::string ID_tmp;
        this->balance = generate_balance();
        unsigned long long total_wallet;
        do {
            ID_tmp = generate_ID();
        } while(std::filesystem::exists(F_POINTS + ID_tmp + ".txt"));

        this->ID = ID_tmp;
        std::ofstream outfile_ID(F_POINTS + ID_tmp + ".txt"); // tên file
        outfile_ID << balance;
        outfile_ID.close();

        std::ifstream infile(file_path1);
        infile >> total_wallet;
        total_wallet -= this->balance;
        infile.close();
        std::ofstream outfile(file_path1);
        outfile << total_wallet;
        outfile.close();

    }
}
void Information::set_full_name(const std::string& _full_name) { this->full_name = _full_name; }
void Information::set_address(const std::string& _address) { this->address = _address; }
void Information::set_country(const std::string& _country) { this->country = _country; }

bool Information::set_phone_number(const std::string& _phone_number) {
    for(const char &c : _phone_number) {
        if(!isdigit(c)) return false;
    }
    this->phone_number = _phone_number;
    return true;
}

bool Information::set_age(std::string _age) {
    reverse(_age.begin(), _age.end());
    while(!_age.empty() && _age.back() == '0') _age.pop_back(); 
    reverse(_age.begin(), _age.end());
    for(char &c : _age) if(!isdigit(c)) return false;
    int _ = _age.size() <= 3 ? stoi(_age) : -1; 

    if(_ < 0) return false;
    this->age = _;
    return true;
}

void Information::set_gender(bool _gender) { this->gender = _gender; }

// Operator overloads
std::istream& operator>>(std::istream& in, Information& data) {
    std::getline(in, data.full_name);
    std::getline(in, data.address);
    std::getline(in, data.country);
    std::getline(in, data.phone_number);
    in >> data.ID;
    in >> data.age;
    in >> data.gender;
    std::ifstream infile(F_POINTS + data.ID + ".txt");
    infile >> data.balance;

    return in;
}

std::ostream& operator<<(std::ostream& out, Information& data) {
    out << data.full_name << "\n"
        << data.address << "\n"
        << data.country << "\n"
        << data.phone_number << "\n"
        << data.ID << "\n"
        << data.age << "\n"
        << data.gender << "\n";
    return out;
}

