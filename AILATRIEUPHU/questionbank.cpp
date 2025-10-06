#include "questionbank.h"
#include <fstream>
#include <iostream>

// ================== Hàm đọc câu hỏi từ file ==================
void QuestionBank::loadFromFiles(const string &quesFile, const string &ansFile) {
    ifstream fq(quesFile);  // Mở file câu hỏi
    ifstream fa(ansFile);   // Mở file đáp án

    if (!fq.is_open() || !fa.is_open()) {
        cerr << "Khong the mo file cau hoi hoac dap an!" << endl;
        return;
    }

    string text, opt;
    vector<string> options;
    char correct;
    int level = 1;

    while (getline(fq, text)) {  // Đọc từng dòng câu hỏi
        if (text.empty()) continue;

        options.clear();
        // Đọc 4 đáp án tiếp theo
        for (int i = 0; i < 4; ++i) {
            if (getline(fq, opt)) options.push_back(opt);
        }

        // Đọc ký tự đáp án đúng từ file answer.txt
        if (!(fa >> correct)) break;
        string temp; getline(fa, temp);  // Bỏ ký tự xuống dòng

        // Tạo đối tượng Question và thêm vào danh sách
        list.push_back(Question(text, options, correct, level));
        ++level;
        if (level > 15) break;  // Chỉ cần 15 câu hỏi
    }

    fq.close();
    fa.close();
}

// ================== Lấy 1 câu hỏi theo chỉ số ==================
Question QuestionBank::getQuestion(int index) {
    if (index >= 0 && index < (int)list.size())
        return list[index];
    return Question();  // Nếu sai index trả về câu hỏi rỗng
}

// ================== Trả về số lượng câu hỏi ==================
int QuestionBank::size() const {
    return list.size();
}
