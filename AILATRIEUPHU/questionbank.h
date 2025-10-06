#pragma once
#include "question.h"
#include <vector>
#include <string>
using namespace std;

// Lớp QuestionBank quản lý danh sách các câu hỏi
class QuestionBank {
private:
    vector<Question> list;   // Danh sách các câu hỏi

public:
    // Nạp dữ liệu từ file câu hỏi và file đáp án
    void loadFromFiles(const string &quesFile, const string &ansFile);

    // Lấy 1 câu hỏi theo chỉ số
    Question getQuestion(int index);

    // Trả về tổng số câu hỏi
    int size() const;
};
