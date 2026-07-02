#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int var[26];

int eval(const string& expr, int& pos);

int parsePrimary(const string& expr, int& pos) {
    if (expr[pos] == '(') {
        pos++;
        int val = eval(expr, pos);
        pos++;
        return val;
    }
    if (islower(expr[pos])) {
        int idx = expr[pos] - 'a';
        if (pos + 1 < expr.size() && expr[pos + 1] == '+') {
            pos += 2;
            return var[idx]++;
        }
        if (pos + 1 < expr.size() && expr[pos + 1] == '-') {
            pos += 2;
            return var[idx]--;
        }
        pos++;
        if (pos < expr.size() && expr[pos] == '+') {
            pos++;
            return ++var[idx];
        }
        if (pos < expr.size() && expr[pos] == '-') {
            pos++;
            return --var[idx];
        }
        return var[idx];
    }
    int num = 0;
    while (pos < expr.size() && isdigit(expr[pos])) {
        num = num * 10 + (expr[pos] - '0');
        pos++;
    }
    return num;
}

int parseMulDiv(const string& expr, int& pos) {
    int left = parsePrimary(expr, pos);
    while (pos < expr.size() && (expr[pos] == '*' || expr[pos] == '/')) {
        char op = expr[pos++];
        int right = parsePrimary(expr, pos);
        if (op == '*') left *= right;
        else left /= right;
    }
    return left;
}

int eval(const string& expr, int& pos) {
    int left = parseMulDiv(expr, pos);
    while (pos < expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
        char op = expr[pos++];
        int right = parseMulDiv(expr, pos);
        if (op == '+') left += right;
        else left -= right;
    }
    return left;
}

int main() {
    string expr;
    int caseNum = 1;
    while (getline(cin, expr)) {
        if (expr.empty()) continue;
        for (int i = 0; i < 26; i++) var[i] = i + 1;
        int pos = 0;
        int result = eval(expr, pos);
        cout << "Expression " << caseNum++ << ": " << result << endl;
    }
    return 0;
}
