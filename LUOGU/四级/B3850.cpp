#include <iostream>
#include <string>
using namespace std;

int reduce(int x) {
    while (x > 9) {
        int s = 0;
        while (x) {
            s += x % 10;
            x /= 10;
        }
        x = s;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        string s;
        cin >> s;
        int len = s.length();
        int sum = 0;
        for (int i = len - 1, pos = 1; i >= 0; i--, pos++) {
            int digit = s[i] - '0';
            if (pos % 2 == 1) {
                digit = reduce(digit * 7);
            }
            sum += digit;
        }
        cout << (sum % 8 == 0 ? "T\n" : "F\n");
    }
    return 0;
}
