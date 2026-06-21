#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int char_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return c - 'a' + 36;
}

char val_char(int v) {
    if (v < 10) return '0' + v;
    if (v < 36) return 'A' + v - 10;
    return 'a' + v - 36;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        string s;
        cin >> a >> b >> s;
        
        vector<int> num;
        for (char c : s) num.push_back(char_val(c));
        
        vector<int> res;
        while (!num.empty()) {
            int carry = 0;
            vector<int> next;
            for (int v : num) {
                carry = carry * a + v;
                if (carry >= b || !next.empty()) {
                    next.push_back(carry / b);
                    carry %= b;
                }
            }
            res.push_back(carry);
            num = next;
        }
        
        reverse(res.begin(), res.end());
        cout << a << " " << s << "\n";
        cout << b << " ";
        for (int v : res) cout << val_char(v);
        cout << "\n\n";
    }
    return 0;
}