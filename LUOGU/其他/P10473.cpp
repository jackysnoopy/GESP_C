#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

struct Node {
    char op;
    long long val;
};

static long long apply_op(long long a, long long b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    if (op == '^') {
        long long res = 1;
        long long base = a;
        long long exp = b;
        while (exp > 0) {
            if (exp & 1LL) res = res * base;
            base = base * base;
            exp >>= 1LL;
        }
        return res;
    }
    return 0;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    vector<Node> nums;
    vector<char> ops;

    auto reduce_top = [&]() {
        char op = ops.back();
        ops.pop_back();
        long long b = nums.back().val;
        nums.pop_back();
        long long a = nums.back().val;
        nums.pop_back();
        nums.push_back({op, apply_op(a, b, op)});
    };

    auto eval = [&]() {
        size_t i = 0;
        while (i < s.size()) {
            if (s[i] == '(') {
                ops.push_back('(');
                ++i;
                continue;
            }
            if (s[i] == ')') {
                while (!ops.empty() && ops.back() != '(') reduce_top();
                if (!ops.empty()) ops.pop_back();
                ++i;
                while (!ops.empty() && ops.back() != '(') reduce_top();
                continue;
            }
            if (isdigit((unsigned char)s[i]) || s[i] == '-') {
                bool neg = false;
                if (s[i] == '-' && (i == 0 || s[i - 1] == '(' || s[i - 1] == '+' ||
                                    s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/' ||
                                    s[i - 1] == '^')) {
                    neg = true;
                    ++i;
                }
                long long x = 0;
                while (i < s.size() && isdigit((unsigned char)s[i])) {
                    x = x * 10 + (s[i] - '0');
                    ++i;
                }
                nums.push_back({0, neg ? -x : x});
                while (!ops.empty() && ops.back() != '(') {
                    if (i < s.size() && s[i] == ')') {
                        reduce_top();
                    } else if (i >= s.size()) {
                        reduce_top();
                    } else {
                        if (precedence(ops.back()) > precedence(s[i]) ||
                            (precedence(ops.back()) == precedence(s[i]) && s[i] != '^')) {
                            reduce_top();
                        } else {
                            break;
                        }
                    }
                }
                continue;
            }
            char op = s[i];
            ++i;
            while (!ops.empty() && ops.back() != '(' &&
                   (precedence(ops.back()) > precedence(op) ||
                    (precedence(ops.back()) == precedence(op) && op != '^'))) {
                reduce_top();
            }
            ops.push_back(op);
        }
        while (!ops.empty()) reduce_top();
    };

    eval();
    cout << nums.back().val << '\n';
    return 0;
}
