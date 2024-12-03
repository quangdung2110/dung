#include<iostream>
#include"Console.cpp"

// bool create_account() {
//     auto generate_password = [&](User &person)->string {
//         string first_name = "", full_name = person.get_full_name();
//         for(int i = full_name.size() - 1; i >= 0 && full_name[i] != ' '; --i) {
//             first_name = full_name[i] + first_name;
//         }

//         return first_name + "&" + to_string(person.get_age()) + "&" + to_string(int(person.get_gender()));
//     };

//     cout << "Tên tài khoản: ";
//     string new_account; cin >> new_account;
//     cout << endl;

//     string file_path1 = folder1 + new_account + ".txt", file_path2 = folder2 + new_account + ".txt";

//     ofstream outfile1(file_path1), outfile2(file_path2);

//     if(fs::exists(file_path1)) {
//         cout << "Tài khoản đã tồn tại" << endl;
//         return 0;
//     }
//     if (!outfile1 || !outfile2) {
//         cerr << "Error" << endl;
//         return 0;
//     }

//     User person; cin >> person;
//     string new_password = generate_password(person);
//     person.set_account(Account(new_account, new_password));

//     // thiếu kiểm tra điều kiện nhập vào
//     outfile1 << person;

//     string hash = bcrypt::generateHash(new_password);
//     outfile2 << hash << endl;

//     outfile1.close();
//     outfile2.close();
//     return 1;
// }


int main() {
	Console IMPLEMENT;
	IMPLEMENT.Start_The_Program();
}