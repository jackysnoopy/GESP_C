#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    // Tidy Numbers：整理数字
    long long ans = n;
    while (true) {
        string s = to_string(ans);
        bool tidy = true;
        for (int i = 1; i < (int)s.length(); i++) {
            if (s[i] > s[i - 1]) {
                tidy = false;
                break;
            }
        }
        
        if (tidy) break;
        ans--;
    }

    cout << ans << "\n";
    return 0;
}
