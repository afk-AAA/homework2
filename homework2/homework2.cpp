#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// 函数声明
bool isBalanced(const string& expr);
string infixToPostfix(const string& expr);
int evaluatePostfix(const string& postfix);
bool isValidExpression(const string& expr); // 新增函數：檢查輸入的有效性

// 主程序
int main() {
    string expression;
    char choice;
    int result;
    do {
        cout << "請輸入運算式 (包含 +, -, *, /, (, ), 數字1~9): ";
        cin >> expression;

        // 檢查表達式格式是否有效
        if (!isValidExpression(expression)) {
            cout << expression << " 不符合格式" << endl;
        }
        // 括號檢查
        else if (!isBalanced(expression)) {
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

// 函数定义：检查表达式的有效性
bool isValidExpression(const string& expr) {
    for (char ch : expr) {
        if (!isdigit(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')') {
            return false; // 若遇到不符合格式的字符，返回false
        }
    }
    return true; // 所有字符均符合格式，返回true
}
