#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long a;
        cin >> a;
        // Find minimum b >= 0 such that a+b has all odd digits
        long long target = a;
        while (true) {
            string s = to_string(target);
            bool ok = true;
            for (char c : s) {
                if ((c - '0') % 2 == 0) { ok = false; break; }
            }
            if (ok) break;
            target++;
        }
        cout << target - a << "\n";
    }
    return 0;
}
