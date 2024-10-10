#include <iostream>  
#include <stack>     // 提供堆疊功能
#include <string> 
#include <cctype>    // 提供字元處理功能，其中用來確定字元是否為大寫字母、數字、標點符號
#include <sstream>   // 專門拿來讀取字串並且處理，很多時候拿來做字串的切割
#include <vector>    // 提供向量功能
#include <map>       // 提供映射功能

using namespace std;

// 宣告函式
bool isBalanced(const string& expr);         // 檢查括號是否對稱
string infixToPostfix(const string& expr);   // 轉換輸入運算式字串為後序表式法
int evaluatePostfix(const string& postfix);  // 計算後序表達式
bool isValidExpression(const string& expr);  // 檢查輸入是否符合格式

int main() {
    string expression;  // 用於存儲輸入的運算式
    char choice;

    do {
        cout << "請輸入運算式(包含 +, -, *, /, (, ), 數字1~9): ";
        cin >> expression;

        if (!isValidExpression(expression)) {   // 檢查是否符合格式
            cout << expression << " 不符合格式" << endl;
        }
        else if (!isBalanced(expression)) {     // 檢查括號是否對稱
            cout << expression << " 運算式的左右括號不對稱，無法繼續運算" << endl;
        }
        else {
            cout << expression << " 運算式的左右括號對稱" << endl;
            string postfix = infixToPostfix(expression);    // 轉換為後序表式法
            cout << expression << " 運算式的後序表式法為: " << postfix << endl;
            int result = evaluatePostfix(postfix);  // 儲存後序表式計算的結果
            cout << expression << " 運算式的運算結果為: " << result << endl;
        }

        cout << "繼續測試請按(Y/y):";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y'); // 若輸入Y或y則繼續重複迴圈

    return 0;
}
               //const所指定物件或變數不可被修改
bool isBalanced(const string& expr) {   // 檢查括號是否對稱
    stack<char> s;  // 創建一個字元堆疊
    for (char ch : expr) { // 定義變數ch，在每次迴圈接收expr(輸入的運算式)中的每個字元
                           // 冒號則是用來分隔迴圈變數和要遍歷的範圍(在這裡是字串 expr)
        if (ch == '(') {
            s.push(ch);  // 若是左括號 '(' ,放入堆疊
        }
        else if (ch == ')') {   // 若是右括號 ')' 時,檢查堆疊            
            if (s.empty() || s.top() != '(') {  // 若堆疊為空或堆疊頂部不是左括號 '(' 
                return false;  // 括號不平衡,回傳false                
            }
            s.pop();  // 彈出放入的左括號 '(' 
        }
    }
    return s.empty();  // 若堆疊空，則括號平衡，返回true
}

string infixToPostfix(const string& expr) { // 轉換輸入運算式字串為後序表式法
    stack<char> s;  /// 創建一個字元堆疊
    stringstream output;  // 用於存儲後序表式的字串流
    map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
    // 設定優先級：數字更高表示更高的優先級

    for (char ch : expr) {  // 重複字串長度之次數，並擷取字元
        if (isdigit(ch)) {  // 判斷變數是否為數字
            output << ch;   // 若是數字，直接輸出到output字串儲存
        }
        else if (ch == '(') {
            s.push(ch);  // 若是左括號 '(' ,放入堆疊
        }
        else if (ch == ')') {
            // 當遇到右括號 ')' 時，彈出堆疊直到遇到左括號 '(' 為止
            while (!s.empty() && s.top() != '(') {
                output << s.top();  // 將堆疊頂部字元輸出到output字串儲存
                s.pop();  // 彈出堆疊頂部字元
            }
            s.pop(); // 彈出左括號 '(' 
        }
        else { // 若是運算子
            while (!s.empty() && precedence[s.top()] >= precedence[ch]) {
                // 當堆疊不空且堆疊頂部的字元優先級高於或等於當前字元時，彈出堆疊
                output << s.top();  // 將堆疊頂部字元輸出到output字串儲存
                s.pop();  /// 彈出堆疊頂部字元
            }
            s.push(ch);  // 將當前字元放入堆疊
        }
    }

    while (!s.empty()) {    // 將堆疊中剩餘的字元全部輸出        
        output << s.top(); // 將堆疊頂部字元輸出
        s.pop(); /// 彈出堆疊頂部字元
    }

    return output.str(); /// 回傳後序表達式
}

int evaluatePostfix(const string& postfix) { // 計算後序表式
    stack<int> s;  // 創建一個整數堆疊
    for (char ch : postfix) {  // 重複後序表式字串長度之次數，並擷取字元
        if (isdigit(ch)) {
            s.push(ch - '0');  // 將字元轉換為整數（例如 '3' 轉換為 3）並放入堆疊
        }
        else { // 若是運算子
            /// 彈出堆疊頂部兩個數字進行運算
            int b = s.top(); s.pop(); /// 先彈出第二個字元
            int a = s.top(); s.pop(); /// 再彈出第一個字元
            switch (ch) {
            case '+': s.push(a + b); break;
            case '-': s.push(a - b); break;
            case '*': s.push(a * b); break;
            case '/': s.push(a / b); break;
            }
        }
    }
    return s.top(); // 回傳堆疊頂部的計算結果
}

bool isValidExpression(const string& expr) { // 檢查輸入是否符合格式
    for (char ch : expr) {
        // 檢查每個字元是否在允許的範圍內
        if (!isdigit(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')') {
            return false; // 若遇到不符合格式的字元,回傳false
        }
    }
    return true; // 所有字元均符合格式,回傳true
}
