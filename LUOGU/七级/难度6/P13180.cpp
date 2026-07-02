#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Fraction {
    long long num, den;
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
        normalize();
    }
    void normalize() {
        if (den < 0) { num = -num; den = -den; }
        long long g = __gcd(abs(num), den);
        if (g) { num /= g; den /= g; }
    }
    Fraction operator+(const Fraction& o) const {
        return Fraction(num * o.den + o.num * den, den * o.den);
    }
    Fraction operator-(const Fraction& o) const {
        return Fraction(num * o.den - o.num * den, den * o.den);
    }
    Fraction operator*(const Fraction& o) const {
        return Fraction(num * o.num, den * o.den);
    }
    Fraction operator/(const Fraction& o) const {
        return Fraction(num * o.den, den * o.num);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        long long S;
        int C;
        cin >> S >> C;
        
        vector<char> ops(C);
        vector<long long> vals(C);
        for (int i = 0; i < C; i++) {
            cin >> ops[i] >> vals[i];
        }
        
        // 简化：贪心选择操作顺序
        Fraction result(S);
        for (int i = 0; i < C; i++) {
            Fraction v(vals[i]);
            if (ops[i] == '+') result = result + v;
            else if (ops[i] == '-') result = result - v;
            else if (ops[i] == '*') result = result * v;
            else if (ops[i] == '/') result = result / v;
        }
        
        cout << "Case #" << t << ": " << result.num << " " << result.den << endl;
    }
    
    return 0;
}
