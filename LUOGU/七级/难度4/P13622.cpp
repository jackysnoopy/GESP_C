#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int zeros = 0, ones = 0;
        for (char c : s[i]) {
            if (c == '0') zeros++;
            else ones++;
        }
        ans += min(zeros, ones);
    }

    cout << ans << "\n";
    return 0;
}
