#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    // Oversized Pancake Flipper：翻转煎饼
    int ans = 0;
    for (int i = 0; i <= n - k; i++) {
        if (s[i] == '-') {
            for (int j = 0; j < k; j++) {
                s[i + j] = (s[i + j] == '+' ? '-' : '+');
            }
            ans++;
        }
    }

    if (s.find('-') != string::npos) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
