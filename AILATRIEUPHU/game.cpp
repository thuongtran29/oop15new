#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

// ================== Hàm khởi tạo ==================
Game::Game() {
    money = 0;                                // Bắt đầu với 0 tiền
    used5050 = usedPhone = usedAudience = false;  // Chưa sử dụng quyền trợ giúp nào
    bank.loadFromFiles("question.txt", "answer.txt"); // Nạp câu hỏi từ file
}

// ================== Hàm trả tiền thưởng ==================
int Game::getPrize(int level) {
    // Danh sách tiền thưởng ứng với 15 câu hỏi
    static int prizes[15] = {200, 400, 600, 1000, 2000, 4000, 6000, 10000,
                             14000, 22000, 30000, 40000, 60000, 85000, 150000};
    if (level >= 1 && level <= 15)
        return prizes[level - 1];
    return 0;  // Mặc định
}

// ================== Trợ giúp 50:50 ==================
void Game::help5050(const Question &q, vector<bool> &hidden) {
    if (used5050) {  // Kiểm tra đã dùng chưa
        cout << "Ban da dung tro giup nay roi!\n";
        return;
    }

    srand(time(0));
    int count = 0;
    while (count < 2) {  // Loại ngẫu nhiên 2 đáp án sai
        int idx = rand() % 4;
        char opt = 'A' + idx;
        if (toupper(opt) != q.getCorrect() && !hidden[idx]) {
            hidden[idx] = true;
            count++;
        }
    }

    used5050 = true;
    cout << "Da loai bo 2 dap an sai!\n";
}

// ================== Trợ giúp Gọi điện thoại ==================
void Game::helpPhone(const Question &q) {
    if (usedPhone) {
        cout << "Ban da dung tro giup nay roi!\n";
        return;
    }

    usedPhone = true;
    cout << "Dang goi cho ban cua ban...\n";
    this_thread::sleep_for(chrono::seconds(2));  // Giả lập thời gian gọi
    cout << "Ban cua ban nghi dap an dung la: " << q.getCorrect() << endl;
}

// ================== Trợ giúp Hỏi khán giả ==================
void Game::helpAudience(const Question &q) {
    if (usedAudience) {
        cout << "Ban da dung tro giup nay roi!\n";
        return;
    }

    usedAudience = true;
    cout << "Dang hoi y kien khan gia...\n";
    this_thread::sleep_for(chrono::seconds(2));

    // Sinh ngẫu nhiên tỉ lệ % cho đáp án đúng cao hơn
    int correct = rand() % 20 + 60;  // 60–80%
    int other = (100 - correct) / 3;

    cout << "Ty le y kien khan gia:\n";
    cout << "A: " << (q.getCorrect() == 'A' ? correct : other) << "%  ";
    cout << "B: " << (q.getCorrect() == 'B' ? correct : other) << "%  ";
    cout << "C: " << (q.getCorrect() == 'C' ? correct : other) << "%  ";
    cout << "D: " << (q.getCorrect() == 'D' ? correct : other) << "%\n";
}

// ================== Hàm bắt đầu trò chơi ==================
void Game::start() {
    if (bank.size() < 15) {  // Kiểm tra số lượng câu hỏi
        cout << "Can it nhat 15 cau hoi trong file!\n";
        return;
    }

    cout << "==== CHAO MUNG DEN VOI AI LA TRIEU PHU ====\n";
    cout << "Nhap A/B/C/D de chon, H=50:50, P=goi ban, G=hoi khan gia, Q=bo cuoc\n\n";

    for (int i = 0; i < 15; i++) {
        Question q = bank.getQuestion(i);  // Lấy câu hỏi thứ i
        vector<bool> hidden(4, false);     // Mảng kiểm soát ẩn đáp án
        q.display();

        cout << "Lua chon cua ban: ";
        char ans;
        cin >> ans;
        ans = toupper(ans);  // Chuyển chữ thường → in hoa

        // Xử lý các lựa chọn đặc biệt
        if (ans == 'Q') {
            cout << "Ban da dung choi. Tong tien: " << money << " VND\n";
            break;
        } else if (ans == 'H') {
            help5050(q, hidden);
            q.display(hidden);
            i--;  // Không tăng câu hỏi (vì chỉ trợ giúp)
            continue;
        } else if (ans == 'P') {
            helpPhone(q);
            i--;
            continue;
        } else if (ans == 'G') {
            helpAudience(q);
            i--;
            continue;
        }

        // Kiểm tra đúng sai
        if (q.checkAnswer(ans)) {
            money = getPrize(i + 1);
            cout << "Dung roi! Ban hien co: " << money << " VND\n\n";
            this_thread::sleep_for(chrono::seconds(1));  // Tạm dừng 1s
        } else {
            cout << "Sai roi! Dap an dung la: " << q.getCorrect() << endl;
            cout << "Tong tien: " << money << " VND\n";
            return;
        }
    }

    cout << "\n🎉 CHUC MUNG BAN DA TRO THANH TRIEU PHU! 🎉\n";
    cout << "So tien thuong cuoi cung: " << money << " VND\n";
}
