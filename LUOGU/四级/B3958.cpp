#include <iostream>
#include <string>
using namespace std;

bool similar(const string &a, const string &b) {
    int la = a.length(), lb = b.length();
    if (la == lb) {
        int diff = 0;
        for (int i = 0; i < la; i++) {
            if (a[i] != b[i]) diff++;
        }
        return diff <= 1;
    }
    if (la - lb == 1) {
        int i = 0, j = 0, op = 0;
        while (i < la && j < lb) {
            if (a[i] != b[j]) {
                i++;
                op++;
            } else {
                i++; j++;
            }
        }
        return op <= 1;
    }
    if (lb - la == 1) {
        int i = 0, j = 0, op = 0;
        while (i < la && j < lb) {
            if (a[i] != b[j]) {
                j++;
                op++;
            } else {
                i++; j++;
            }
        }
        return op <= 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string a, b;
        cin >> a >> b;
        cout << (similar(a, b) ? "similar\n" : "not similar\n");
    }
    return 0;
}
