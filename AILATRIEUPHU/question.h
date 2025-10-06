#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Lớp Question mô tả một câu hỏi trong trò chơi
class Question {
private:
    string text;              // Nội dung câu hỏi
    vector<string> options;   // Danh sách 4 đáp án
    char correct;             // Đáp án đúng (A/B/C/D)
    int level;                // Mức độ hoặc số thứ tự câu hỏi

public:
    // Hàm khởi tạo câu hỏi
    Question(string t = "", vector<string> opts = {}, char c = 'A', int lvl = 1);

    // Hiển thị câu hỏi ra màn hình (có thể ẩn 1 số đáp án nếu dùng 50:50)
    void display(const vector<bool> &hidden = {false, false, false, false});

    // Kiểm tra xem đáp án người chơi nhập có đúng không
    bool checkAnswer(char ans);

    // Lấy ký tự đáp án đúng
    char getCorrect() const;

    // Lấy cấp độ câu hỏi
    int getLevel() const;
};
