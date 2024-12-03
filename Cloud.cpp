#include "Cloud.h"

void Cloud::backup() {
    std::string command, commit_msg;

    // Lấy thời gian hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    
    // Thêm tất cả các tệp vào staging
    command = "git add . > nul 2>&1";
    std::system(command.c_str());

    // Commit với thông điệp thời gian hiện tại
    commit_msg = std::string(buffer);
    command = "git commit -m \"" + commit_msg + "\" > nul 2>&1";
    std::system(command.c_str());

    // Đẩy thay đổi lên nhánh chính (hoặc nhánh mong muốn)
    command = "git push origin main > nul 2>&1";
    std::system(command.c_str());
}

void Cloud::restore(std::string position) {
    std::string command;

    if (is_tracked(position)) {
        // Nếu tệp đã được theo dõi, sử dụng git restore
        command = "git restore --source=origin/main " + position + " --staged > nul 2>&1";
    } else {
        // Nếu tệp không được theo dõi và không có trong kho local, dùng git clean
        command = "git clean -f > nul 2>&1";
    }

    // Thực thi lệnh
    std::system(command.c_str());
}

bool Cloud::is_tracked(std::string position) {
    // Kiểm tra xem tệp có được Git theo dõi không
    std::string command = "git ls-files --error-unmatch " + position + " > nul 2>&1";

    int result = std::system(command.c_str());

    // Nếu result là 0, tức là tệp đã được Git theo dõi
    return (result == 0);
}