/*

#include <iostream>  // 包含輸入輸出相關的標頭檔
#include <stack>     // 包含堆疊的相關標頭檔
#include <string>    // 包含字串的相關標頭檔
#include <cctype>    // 包含字符處理函數的相關標頭檔
#include <sstream>   // 包含字串流的相關標頭檔
#include <vector>    // 包含向量的相關標頭檔
#include <map>       // 包含映射的相關標頭檔

using namespace std;

// 函数声明
bool isBalanced(const string& expr);                // 檢查括號是否平衡
string infixToPostfix(const string& expr);         // 中缀表达式转后缀表达式
int evaluatePostfix(const string& postfix);         // 計算後序表達式的結果

// 主程序
int main() {
    string expression;  // 用於存儲用戶輸入的運算式
    char choice;        // 用於存儲用戶是否繼續的選擇
    int result;         // 存儲計算結果

    do {
        cout << "請輸入運算式 (包含 +, -, *, /, (, ), 數字1~9): ";
        cin >> expression;  // 讀取用戶輸入的運算式

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

        // 詢問用戶是否繼續
        cout << "繼續測試請按(Y/y):";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y'); // 若用戶選擇繼續，則重複進入循環

    return 0; // 返回0，表示程式正常結束
}

// 函数定义：检查括号是否平衡
bool isBalanced(const string& expr) {
    stack<char> s;  // 創建一個字符堆疊
    for (char ch : expr) {  // 遍歷每個字符
        if (ch == '(') {
            s.push(ch);  // 若是左括號，推入堆疊
        }
        else if (ch == ')') {
            if (s.empty() || s.top() != '(') {  // 若堆疊為空或頂部不是左括號
                return false;  // 括號不平衡
            }
            s.pop();  // 弹出匹配的左括號
        }
    }
    return s.empty();  // 若堆疊空，則括號平衡
}

// 函数定义：中缀表达式转后缀表达式
string infixToPostfix(const string& expr) {
    stack<char> s;  // 創建一個字符堆疊
    stringstream output;  // 用於存儲後序表達式
    map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} }; // 操作符優先級

    for (char ch : expr) {  // 遍歷每個字符
        if (isdigit(ch)) {
            output << ch;  // 若是數字，直接輸出
        }
        else if (ch == '(') {
            s.push(ch);  // 若是左括號，推入堆疊
        }
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {  // 當堆疊不空且頂部不是左括號
                output << s.top();  // 將堆疊頂部操作符輸出
                s.pop();  // 彈出堆疊頂部操作符
            }
            s.pop(); // 彈出 '('
        }
        else { // 若是操作符
            while (!s.empty() && precedence[s.top()] >= precedence[ch]) { // 檢查堆疊頂部的優先級
                output << s.top();  // 將堆疊頂部操作符輸出
                s.pop();  // 彈出堆疊頂部操作符
            }
            s.push(ch);  // 將當前操作符推入堆疊
        }
    }

    // 將堆疊中剩餘的操作符全部輸出
    while (!s.empty()) {
        output << s.top();
        s.pop();
    }

    return output.str(); // 返回後序表達式
}

// 函数定义：计算后缀表达式
int evaluatePostfix(const string& postfix) {
    stack<int> s;  // 創建一個整數堆疊

    for (char ch : postfix) {  // 遍歷後序表達式的每個字符
        if (isdigit(ch)) {
            s.push(ch - '0');  // 將字符轉換為整數並推入堆疊
        }
        else { // 若是操作符
            int b = s.top(); s.pop();  // 彈出堆疊頂部兩個數字
            int a = s.top(); s.pop();
            switch (ch) {  // 根據操作符計算
            case '+': s.push(a + b); break; // 加法
            case '-': s.push(a - b); break; // 減法
            case '*': s.push(a * b); break; // 乘法
            case '/': s.push(a / b); break; // 除法
            }
        }
    }

    return s.top(); // 返回堆疊頂部的結果
}
*/

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
