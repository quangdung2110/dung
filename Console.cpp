#include "Console.h"
#include <algorithm>


Console::Console() {
    // cur = nullptr;
}


void Console::reset() {
    // cur = nullptr;
    cur.set_account(Account(), 1);
    cur.set_information(Information(), 1);
}


void Console::print(int x, int y, std::string s) {
    Menu::gotoxy(x, y);
    std::cout << s;
}

std::string Console::input(int x, int y, bool isPlus, bool ispassword, int mn) {
    std::string res = "";
    char ch;
    bool clearedPrompt = false;

    Menu::gotoxy(x, y);
    while (true) {
        ch = _getch();
            
        if(ch == 9) {	//tab
            return "";
        }
        if(isPlus && ch == 43) {	// neu dang nhap thi co tao tai khoan moi
            return "+";
        }
        if (res.length() >= 38 && ch != 8 && ch != 13) {
            continue; 
        }

        if (ch == 13) { // Enter
            if(res.length() >= mn) break; //toi thieu ki tu
            else continue;
                
        } else if (ch == 8) { // Backspace
            if (!res.empty()) {
                res.pop_back();
                Menu::gotoxy(x + res.length(), y);
                std::cout << ' ';
                Menu::gotoxy(x + res.length(), y);
            }
        } else {
            if (!clearedPrompt) {
                std::cout << "                                      "; // Xóa nhãn "Enter username:"
                Menu::gotoxy(x, y);
                clearedPrompt = true;
            }
            res.push_back(ch);
            
            if(ispassword) {
                std::cout << "*";	
            }
            else {
                std::cout << ch;
            }
        }
    }
    return res;
}


std::string Console::change(std::string& title, std::string& enter_new, std::string& old_ans, bool age, bool gender, bool phone_number) {
    Menu::print_otp();
    Menu::gotoxy(53,3);
    std::cout << title;
    Menu::gotoxy(51,6);
    std::cout << enter_new << ":";
    Menu::gotoxy(41,6);
            
    char ch;
    bool clearedPrompt = false;
    std::string ans = "";
    int mn;

    if(age) mn = 1;
    else if(gender) mn = 1;
    else if(phone_number) mn = 10;
    else mn = 5;

    while (true) {
        ch = _getch();
        
        if(ch == 9) return "";	// tab: back
        
        if (ans.length() >= 38 && ch != 8 && ch != 13) {
            continue; 
        }
    
        if (ch == 13) { // Enter
            if(ans.length() >= mn) break;
            else continue;
        } else if (ch == 8) { // Backspace
            if (!ans.empty()) {
                ans.pop_back();
                Menu::gotoxy(41 + ans.length(), 6);
                std::cout << ' ';
                Menu::gotoxy(41 + ans.length(), 6);
            }
        } else {
            if (!clearedPrompt) {
                std::cout << "                                      ";
                Menu::gotoxy(41, 6);
                clearedPrompt = true;
            }
            ans.push_back(ch);
            std::cout << ch;
        }
    }
    int _ = gotp::verify_otp(9);
    if(_ == 6) return "";

    if(_ == 5) {
        Menu::notification("Incorrect OTP!", 52, 5);
        ans = change(title, enter_new, old_ans, 0, 0, 0);
    }

    else if(age) {
        
        //chuaw xong
        if(!cur.Information::set_age(ans)) {
            Menu::notification("Invalid information!", 40, 5);
            ans = change(title, enter_new, old_ans, age, gender, phone_number);
        }
    }
    else if(gender) {
        if(ans != "1" && ans != "0") {
            Menu::notification("Invalid information!", 49, 5);
            ans = change(title, enter_new, old_ans, age, gender, phone_number);
        }
    }
    else if(phone_number) {
        if(!cur.Information::set_phone_number(ans)) {
          Menu::notification("Invalid information!", 49, 5);
          ans = change(title, enter_new, old_ans, age, gender, phone_number);
        }
    }
    else if(ans == old_ans) {
        Menu::notification("Duplicate Old Information!", 47, 5);
        ans = change(title, enter_new, old_ans, 0, 0, 0);
    }

    if(ans != "") {
        Menu::notification("----Successful Operation----", 45, 5);
    }
    return ans;
}




void Console::change_information(bool manager) {
    char c; 
    while (true) {
        Menu::print_change_information();
        Menu::gotoxy(4, 27);
        std::cout << "--> Enter your choice: ";

        c = _getch(); 
        std::cout << c;
        Sleep(200);
        
        if(c == 9) return;
        
        if (c < '1' || c > '8') {
            Menu::notification("Invalid result!!!", 50, 5);
        }
        if(manager && c == '2') {
            Menu::notification("The manager isn't  allowed to change the password", 37, 5);
            continue;
        }

        
        switch (c) {
            
            case '1': {//full name
                std::string old_name = cur.get_full_name(); /* NAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMMMMMMMMMMMMMMMMMMMMMMMMMMMMeeeeeeeeeeeeeeeeeeee*/;
                std::string title = "FULL NAME";
                std::string enter_new = "fullname";
                std::string name = change(title, enter_new, old_name, 0, 0, 0);
                if(name != "") cur.set_full_name(name);
                // if !name.emmtpy() thi luu lai, lam voi tat ca cac truong hop o ben duoi ======== =======================================
                break;
            }
            
            case '2': {// password
                std::string old_password = cur.get_account().get_password(); /* PASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSWWORDDDDDDDDD?*/;
                std::string title = "PASSWORD";
                std::string enter_new = "password";
                std::string password_current = change(title, enter_new, old_password, 0, 0, 0);
                if(password_current != "") cur.get_account().set_password(password_current);
                break;  
            }	
            
            case '3': {//address
                std::string old_address = cur.get_address();/*ADDRESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS*/;
                std::string title = "ADDRESS";
                std::string enter_new = "address";
                std::string address = change(title, enter_new, old_address, 0, 0, 0);
                if(address != "") cur.set_address(address);
                break;
            }

            case '4': {
                std::string old_age = std::to_string(cur.get_age());
                std::string title = "AGE";
                std::string enter_new = "age";
                std::string age = change(title, enter_new, old_age, 1, 0, 0);
                if(age != "") cur.set_age(age);
                break;
            }

            case '5': {
                std::string old_gender = std::to_string(int(cur.get_gender()));
                std::string title = "GENDER";
                std::string enter_new = "gender (Male: 1, Female: 0)";
                std::string gender = change(title, enter_new, old_gender, 0, 1, 0);
                if(gender != "") cur.set_gender(bool(gender[0] - '0'));
                break;
            }

            case '6': {
                std::string old_phone_number = cur.get_phone_number();
                std::string title = "PHONE NUMBER";
                std::string enter_new = "phone number";
                std::string phone_number = change(title, enter_new, old_phone_number, 0, 0, 1);
                if(phone_number != "") cur.set_phone_number(phone_number);
                break;
            }

            case '7': {
                std::string old_country = cur.get_country(); //Country ========================================================
                std::string title = "COUNTRY";
                std::string enter_new = "country";
                std::string country = change(title, enter_new, old_country, 0, 0, 0);
                if(country != "") cur.set_country(country);
                break;
            }
        }
        
        if(c == '2') {
            std::ofstream outfile(F_PASSWORD + cur.get_account().get_user_name() + ".txt");
            outfile << bcrypt::generateHash(cur.get_account().get_password());
        } else {
            std::ofstream outfile(F_INFORMATION + cur.get_account().get_user_name() + ".txt");
            outfile << cur;
        }
    }
    Cloud::backup();
}


void Console::print_information(){
    Menu::identification_information();
    // std::string balance;
    // std::ifstream infile(F_POINTS + cur.Information::get_ID() + ".txt");
    // infile >> balance;
    // infile.close();

    print(48, 4, cur.Information::get_full_name());

    print(48, 5, std::to_string(cur.Information::get_age()));

    print(48, 5, (cur.Information::get_gender() == 1 ? "Male" : "Female"));

    // std::string tmp = "aaaaaaaaaaaaaa";  //account balance=================================================;
    // std::string balance = "";

    // for (int i = tmp.size() - 1, count = 0; i >= 0; --i, ++count) {
    //     balance = tmp[i] + balance;
    //     if (count == 2 && i != 0) {
    //         balance = "," + balance;
    //         count = -1; //
    //     }
    // }
    print(48, 11, std::to_string(cur.Information::get_balance()) + " Points");

    // std::string phone_number = "aaaaaaaaaa"; //phone number==========================================
    print(48, 12, cur.Information::get_phone_number());

    // std::string country = "aaaaaaaaa"; //country ======================================
    print(48, 13, cur.Information::get_country());

    Menu::gotoxy(5, 20);
    char ch;
    while(1) {
        ch = _getch();
        if(ch != 9)
            continue;
        else break;
    }
}


void Console::transfer_money() {
    Menu::transfer_money_screen();

    std::string amount = input(41, 6, 0, 0, 1);
    if(amount == "") return;


    std::string ID = input(41, 9, 0, 0, 12);
    if(ID == "") return;

    //1->"Account does not exist! "
    //2->"Transaction error please try again!"
    //3->"Invalid amount !"
    //4->"Insufficient balance !"
    //5->"OTP is incorrect !"
    //6->"tab"
    //7->"OTP is correct !"
    //8->error

    char ch = cur.transfer_money(ID, amount) + '0';

    switch (ch) {
        case '1':
            Menu::notification("Account does not exist!", 47, 5); // chưa check vị trí
            break;
        case '2':
            Menu::notification("Transaction error, please try again!", 42, 5); // chưa check vị trí
            break;
        case '3':
            Menu::notification("Invalid amount!", 50, 5);
            break;
        case '4':
            Menu::notification("Insufficient balance!", 49, 5);
            break;
        case '5':
            Menu::notification("OTP is incorrect!", 50, 5);
            break;
        case '6':
            //tab
            return;
        case '7':
            Menu::notification("--You have successfully transferred the money--", 37, 5);
            break;
        case '8':
            //restore
            break;
    }

    transfer_money();
    Cloud::backup();
    return;
}


void Console::transaction_history() {
    Menu::print_transaction_history();

    std::ifstream infile(F_USER_TRANSACTION_HISTORY + cur.get_ID() + ".txt");
    std::string sentence;
    std::cout << "    ";
    while(getline(infile, sentence)) {
        std::cout << sentence << std::endl << "    ";
    }

    char ch;
    while(true) {
        ch = _getch();
        if(ch == 9) return;
    }
}


void Console::log_in_useraccount() {
    while(true) {
        Menu::print_log_in_user_account();
        std::string username = input(41, 3, 0, 0, 1);

        if(username == "") return;
        if(std::filesystem::exists(F_INFORMATION + username + ".txt")) {
            std::ifstream infile(F_INFORMATION + username + ".txt");
            // cur = new User();
            infile >> static_cast<Information&>(cur);
            cur.set_account(Account(username, ""), 1);
            infile.close();
            user_operation(1);

        } else {
            Menu::notification("username does not exist", 49, 5);
            continue;            
        }   
    }
}


void Console::view_list_of_users_account() {
    Menu::print_list_of_user();

for (const auto& entry : fs::directory_iterator(F_INFORMATION)) {
    if (entry.is_regular_file()) { 
        std::ifstream infile(entry.path());
        Information tmp;

        infile >> tmp;
        std::cout << std::left
            << std::setw(20) << tmp.get_ID()             // ID WALLET
            << std::setw(20) << tmp.get_full_name()      // FULL NAME
            << std::setw(21) << tmp.get_phone_number()   // PHONE NUMBER
            << std::setw(10) << tmp.get_balance()    // POINTS
            << std::setw(20) << tmp.get_address()        // ADDRESS
            << tmp.get_country()                         // COUNTRY
            << std::endl << "    ";
    }
}



    
    char c;
    while(true) {
        c = _getch();
        if(c == 9) return;
    }
}


void Console::list_of_users() {
    while(true) {
        Sleep(100);
        Menu::print_list_of_users_main();
        Menu::gotoxy(4,27);
        std::cout << "--> Enter your choice: ";

        char c;
        c = _getch();
        std::cout << c;
        Sleep(200);

        if(c == 9) {
            break;
        }
        if(c < '1' || c > '2') {
            Menu::notification("Invalid result !", 52, 5);
            continue;
        }

        switch(c) {
            case '1': {
                log_in_useraccount();
                break;
            }
            case '2': {
                view_list_of_users_account();
                break;
            }
        }
    }
}
bool Console::create_account() {
    Menu::create_account_screen();
    
    Account tmp1; Information tmp2;
    std::string username = input(21, 6, false, false, 1);

    if(username == "") return 1; //tab
    else {
        std::string file_path = F_INFORMATION + username + ".txt";
        if(std::filesystem::exists(file_path)) {
            Menu::notification("Username already exist!", 48, 5); // chưa check
            return 0;
        } else {
            tmp1.set_user_name(username);
        }
    }

    std::string password = input(21, 9, false, true, 8);
    if(password == "") return 1;
    else {
        if(!tmp1.set_password(password)) {
            system("cls");
            std::cout << R"(
                             _____________________________________________________________
                            |                                                             |
                            |                    O~~~NOTIFICATION~~~O                     |
                            |                                                             |
                            |          Password must contain at least 1 uppercase,        |
                            |           lowercase, number, special character and          |
                            |             must not contain invalid characters!            |
                            |                                                             |
                            |_____________________________________________________________|)";
            Menu::gotoxy(5, 20);
            Sleep(4000);
            return 0;
        }
    }
    
    std::string password_again = input(21, 12, false, true, 8);
    if(password_again == "") return 1;
    
    if(password != password_again) {
        Menu:: notification("Password is incorrect!", 48, 5);
        return 0;
    }

    std::string phone;
    while(true) {
        phone = input(21, 15, false, false, 10);
        if(phone == "") return 1;
        else {
            if(!tmp2.set_phone_number(phone)) {
                print(21, 15, "Phone number is incorrect!            "); // không rõ
                Sleep(1000);
                print(21, 15, "                                      ");
                continue;
            } else break;
        }
    }

    std::string fullname = input(62, 6, false, false, 5);
    tmp2.set_full_name(fullname);
    
    std::string age;
    while(true) {
        age = input(62, 9, false, false, 1);    
        if(age == "") return 1; // tab

        if(!tmp2.Information::set_age(age)) {
            print(62, 9, "Age is incorrect !!!                  ");
            Sleep(1000);
            print(62, 9, "                                      ");
        }
        else break;   
    }

    char ch;
    while(true) {
        Menu::gotoxy(62, 12);
        ch = _getch();
        std::cout << "                                       ";
        Menu::gotoxy(62, 12);

        if(ch == 9) return 1; // tab
        if(ch == '0' || ch == '1') {
            tmp2.set_gender(ch);
            std::cout << ch;
            break;
        }
    }
    std::string address = input(62, 15, false, false, 5);
    if(address == "") return 1;
    std::string country = input(62, 18, false, false, 5);
    if(country == "") return 1;
    
    tmp2.set_address(address);
    tmp2.set_country(country);
    // luu 9 thong tin lại =======================================================================================;
    Menu::notification("Account created successfully", 45, 5);
    User new_user(tmp2, tmp1);
    Cloud::backup();
    return 1; // tro ve đăng nhập
}

// chưa check kĩ
void Console::create_user_account() {
    while(true) {
        Menu::create_account_for_user_screen();
        Account tmp1; Information tmp2;

        std::string username = input(41, 6, 0, 0, 1);
        if(username == "") return;
        
        if(std::filesystem::exists(F_PASSWORD + username + ".txt")) {
            Menu::notification("Username already exist!", 48, 5);
            continue;
        } else {
            tmp1.set_user_name(username);
        }
        

        std::string password;

        std::string fullname = input(41, 9, 0, 0, 1);
        if(fullname == "") return;
        tmp2.set_full_name(fullname);
        for(char &c : fullname) tolower(c);


        std::string age;
        while(true) {
            age = input(41, 12, false, false, 1);

            if(age == "") return;
            if(!tmp2.Information::set_age(age)) {
                print(41, 12, "Age is incorrect !!!                  ");
                continue;
            } else break;
        }

        char ch;
        while(true) {
            Menu::gotoxy(41, 15);
            ch = _getch();
            std::cout << "                                       ";
            Menu::gotoxy(41, 15);

            if(ch == 9) return; // tab
            if(ch == '0' || ch == '1') {
                tmp2.set_gender(ch);
                std::cout << ch;
                break;
            }
        }

        password = fullname +  '&' + age + '&' + ch;
        tmp1.set_password(password, 1);

        std::string phone;
        while(true) {
            phone = input(41, 18, false, false, 10);
            if(phone == "") return;
            else {
                if(!tmp2.set_phone_number(phone)) {
                    print(41, 18, "Phone number is incorrect!            "); // không rõ
                    Sleep(1000);
                    print(41, 18, "                                      ");
                    continue;
                } else break;
            }
        }

        std::string address = input(41, 21, false, false, 5);
        if(address == "") return;
        std::string country = input(41, 24, false, false, 5);
        if(country == "") return;

        // luu std ==========================================================
        tmp2.set_address(address);
        tmp2.set_country(country);
        User new_user(tmp2, tmp1);
        Cloud::backup();

        Menu::notification("Account created successfully", 45, 5);
        return;
    }
}


void Console::system_transaction_history() {
    Menu::system_transaction_history_screen();
    std::ifstream infile(F_TRANSACTION_LOG);
    std::string sentence, transaction_time = "", transaction = "";
    int i;
    std::cout << "    ";
    while(getline(infile, sentence)) {
        i = 0; transaction = ""; transaction_time = "";
        while(i < sentence.size() && sentence[i] != ' ') transaction_time += sentence[i++];
        while(i < sentence.size()) transaction += sentence[++i];
        std::cout << transaction_time << "            " << transaction << std::endl << "        ";

    }
    infile.close();
    char ch;
    while(true) {
        ch = _getch();
        if(ch == 9) return;
    }
}


void Console::user_operation(bool manager) {
    while(true) {	// menu
        Sleep(100);
        Menu::print_user_menu();
        Menu::gotoxy(4,27);
        std::cout << "--> Enter your choice: ";

        char c;
        c = _getch();
        std::cout << c;
        Sleep(200);

        if(c == 9) {
            break;
        }
        if(c < '1' || c > '4') {
            Menu::notification("Invalid result !", 52, 5);
            continue;
        }

        switch (c) {
            case '1': {
                change_information(manager);
                break;
            }
            case '2' : {
                print_information();
                break;
            }
            case '3' : {
                transfer_money();
                break;
            }
            case '4' : {
                transaction_history();
                break;
            }
        }
    }
}


void Console::manager_opertion() {
    while(true) {	// menu
        Sleep(100);
        Menu::print_manager_menu();

        Menu::gotoxy(4,27);
        std::cout << "--> Enter your choice: ";
        char c;
        c = _getch();
        std::cout << c;
        Sleep(200);

        if(c == 9) {
            break;
        }
        if(c < '1' || c > '3') {
            Menu::gotoxy(5, 10);
            Menu::notification("Invalid result!", 52, 5);
            continue;
        }

        switch (c) {
            case '1': {
                list_of_users();
                break;
            }
            case '2' : {
                create_user_account();
                break;
            }
            case '3' : {
                system_transaction_history();
                break;
            }
        }
    }
}


bool Console::create_password() {
    Menu::print_create_password();

    std::string password = input(41, 6, false, true, 8);
    if(password == "") return 1;

    if(!cur.get_account().valid_password(password)) {
        system("cls");
         std::cout << R"(
                             _____________________________________________________________
                            |                                                             |
                            |                    O~~~NOTIFICATION~~~O                     |
                            |                                                             |
                            |          Password must contain at least 1 uppercase,        |
                            |           lowercase, number, special character and          |
                            |             must not contain invalid characters!            |
                            |                                                             |
                            |_____________________________________________________________|)";
        Menu::gotoxy(5, 20);
        Sleep(4000);
        return 0;
    } 
    std::string password_again = input(41, 9, false, true, 8);
    if(password_again == "") return 1;

    if(password != password_again) {
        Menu::notification("Password is incorrect!", 48, 5);
        return 0;
    }

    cur.get_account().set_password(password);
    std::ofstream outfile(F_PASSWORD + cur.get_account().get_user_name() + ".txt");
    outfile << bcrypt::generateHash(password);
    
    Menu::notification("Password created successfully", 45, 5);
    Cloud::backup();
    // luu lai ================================================================================================
    return 1;
}


void Console::Start_The_Program() {

    while(true) {	// Login
        Console::reset();

    	Menu::print_login_frame();
    	
    	std::string user_name = Console::input(41, 7, true, false, 1); //username

    	if(user_name == "") { // end
    		break;
		}
		if(user_name == "+") {	// create account
			while(true) {
				if(Console::create_account() == 1) { // bam tab
					break;
				}
			}
			continue; // tro ve giao dien dang nhap
		}
                        
        
        


        std::string password = Console::input(41, 10, true, true, 8);

		
		if(password == "") { // end
    		break;
		}
		if(password == "+") {	// create accont
			while(true) {
				if(Console::create_account() == 1) { // bam tab
					break;
				}
			}
			continue; // tro ve giao dien dang nhap
		}
        bool user; // truong hop quan li

        if(un_manager == user_name && pw_manager == password) {
            user = false;
        } else {
            if(std::filesystem::exists(F_PASSWORD + user_name + ".txt")) {
                std::ifstream infile(F_PASSWORD + user_name + ".txt");
                std::string valid_password;
                infile >> valid_password;
                infile.close();
                if(!bcrypt::validatePassword(password, valid_password)) {
                    Menu::notification("Incorrect username or password", 45, 5);
                    continue; // khoong ro
                }            
            } else {
                Menu::notification("Incorrect username or password", 45, 5);
                continue;
            }
            cur.set_account(Account(user_name, password), 1);
            std::ifstream infile(F_INFORMATION + user_name + ".txt");
            
            infile >> static_cast<Information&>(cur);
            if(cur.get_account().is_auto_password(cur.get_full_name(), cur.get_age(), cur.get_gender())) {
                while(true) {
                    if(Console::create_password() == 1) { // bam tab hoac dang ki thanh cong
                        break;
                    }
                }
                continue; // tro ve giao dien dang nhap
            }
            

            user = true;
        }

        // kiem tra la quan li hay user, neu la quan li user = 0, neu la user -> user = 1 ==========================================================

        if(user) {
            user_operation(0);
        }
        else {
            manager_opertion();
        }
	}
	Menu::notification("The program has ended", 49, 5); // Thong bao ket thuc
    return;
}