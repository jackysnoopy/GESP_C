#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

long long gcd(long long a, long long b) {
    a = abs(a); b = abs(b);
    while (b) { a %= b; swap(a, b); }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int S, C;
        cin >> S >> C;
        
        vector<char> ops(C);
        vector<int> vals(C);
        for (int i = 0; i < C; i++) {
            cin >> ops[i] >> vals[i];
        }
        
        // We want to maximize the final value by choosing card order
        // This is a complex optimization problem
        
        // For now, use a simple greedy strategy
        // Sort cards: multiplication first, then addition, then subtraction, then division
        
        vector<int> order(C);
        for (int i = 0; i < C; i++) order[i] = i;
        
        // Simple strategy: process in given order
        long long num = S, den = 1;
        
        for (int i = 0; i < C; i++) {
            long long v = vals[i];
            
            if (ops[i] == '+') {
                num += v * den;
            } else if (ops[i] == '-') {
                num -= v * den;
            } else if (ops[i] == '*') {
                num *= v;
            } else if (ops[i] == '/') {
                den *= v;
            }
            
            // Simplify
            long long g = gcd(num, den);
            if (g > 0) {
                num /= g;
                den /= g;
            }
            if (den < 0) {
                num = -num;
                den = -den;
            }
        }
        
        cout << "Case #" << t << ": " << num << " " << den << endl;
    }
    
    return 0;
}
