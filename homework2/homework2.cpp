// homework2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// 函数声明
bool isBalanced(const string& expr);
string infixToPostfix(const string& expr);
int evaluatePostfix(const string& postfix);

// 主程序
int main() {
    string expression;
    char choice;
    int result;
    do {
        cout << "請輸入運算式 (包含 +, -, *, /, (, ), 數字1~9): ";
        cin >> expression;

        // 括號檢查
        if (!isBalanced(expression)) {
            cout << expression << " 運算式的左右括號不對稱，無法繼續運算" << endl;
        }
        else {
            cout << expression << " 運算式的左右括號對稱" << endl;
        // 轉換為後序表式法
        string postfix = infixToPostfix(expression);
        cout << expression << " 運算式的後序表式法為： " << postfix << endl;

        // 計算後序表式的結果
        result = evaluatePostfix(postfix);
        cout << expression << " 運算式的運算結果為： " << result << endl;
        }
        cout << "繼續測試請按(Y/y):";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    return 0;
}

// 函数定义：检查括号是否平衡
bool isBalanced(const string& expr) {
    stack<char> s;
    for (char ch : expr) {
        if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            if (s.empty() || s.top() != '(') {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

// 函数定义：中缀表达式转后缀表达式
string infixToPostfix(const string& expr) {
    stack<char> s;
    stringstream output;
    map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

    for (char ch : expr) {
        if (isdigit(ch)) {
            output << ch; // 如果是数字，直接输出
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                output << s.top();
                s.pop();
            }
            s.pop(); // 弹出 '('
        }
        else { // 操作符
            while (!s.empty() && precedence[s.top()] >= precedence[ch]) {
                output << s.top();
                s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.empty()) {
        output << s.top();
        s.pop();
    }

    return output.str();
}

// 函数定义：计算后缀表达式
int evaluatePostfix(const string& postfix) {
    stack<int> s;

    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0'); // 转换字符为数字
        }
        else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            switch (ch) {
            case '+': s.push(a + b); break;
            case '-': s.push(a - b); break;
            case '*': s.push(a * b); break;
            case '/': s.push(a / b); break;
            }
        }
    }

    return s.top(); // 返回结果
}


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
