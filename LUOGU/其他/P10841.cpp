#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        int segs = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] != s[i-1]) segs++;
        }
        if (segs == 1) {
            cout << (n % 2 == 0 ? n / 2 + 1 : (n + 1) / 2) << "\n";
        } else {
            cout << n - segs / 2 << "\n";
        }
    }
    return 0;
}
