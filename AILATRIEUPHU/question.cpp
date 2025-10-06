#include "question.h"

// ================== Hàm khởi tạo ==================
Question::Question(string t, vector<string> opts, char c, int lvl)
    : text(t), options(opts), correct(toupper(c)), level(lvl) {}

// ================== Hiển thị câu hỏi ==================
void Question::display(const vector<bool> &hidden) {
    cout << "===== Cau hoi so " << level << " =====" << endl;
    cout << text << endl;
    char opt = 'A';
    for (int i = 0; i < 4; i++) {
        if (!hidden[i]) {  // Nếu đáp án này không bị ẩn
            cout << opt << ") " << options[i] << "\t";
            if ((i + 1) % 2 == 0) cout << endl;
        }
        opt++;
    }
    cout << endl;
}

// ================== Kiểm tra đáp án ==================
bool Question::checkAnswer(char ans) {
    return toupper(ans) == correct;
}

// ================== Trả về đáp án đúng ==================
char Question::getCorrect() const {
    return correct;
}

// ================== Lấy số thứ tự câu hỏi ==================
int Question::getLevel() const {
    return level;
}
