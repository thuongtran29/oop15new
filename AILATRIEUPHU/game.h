#pragma once                     // Tránh include nhiều lần file header
#include "questionbank.h"         // Gọi đến lớp QuestionBank (quản lý danh sách câu hỏi)
#include <vector>                 // Sử dụng vector cho danh sách đáp án bị ẩn

// Lớp Game quản lý toàn bộ logic trò chơi
class Game {
private:
    QuestionBank bank;            // Ngân hàng câu hỏi
    int money;                    // Số tiền thưởng hiện tại
    bool used5050, usedPhone, usedAudience;  // Cờ đánh dấu đã dùng các quyền trợ giúp chưa

    // Các hàm trợ giúp nội bộ (không gọi từ ngoài lớp)
    void help5050(const Question &q, vector<bool> &hidden); // Quyền trợ giúp 50:50
    void helpPhone(const Question &q);                      // Quyền gọi điện thoại cho bạn
    void helpAudience(const Question &q);                   // Quyền hỏi ý kiến khán giả
    int getPrize(int level);                                // Hàm trả về tiền thưởng theo mức độ câu hỏi

public:
    Game();        // Hàm khởi tạo, thiết lập ban đầu và tải dữ liệu câu hỏi
    void start();  // Hàm bắt đầu trò chơi chính
};
