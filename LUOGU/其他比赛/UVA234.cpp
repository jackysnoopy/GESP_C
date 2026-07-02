#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isPalin(const string& s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

int main() {
    int t = 0;
    int n;
    while (cin >> n && n) {
        vector<string> words(n);
        for (int i = 0; i < n; i++) cin >> words[i];
        string s;
        for (int i = 0; i < n; i++) s += words[i];
        int len = s.length();
        vector<int> dp(len, 0);
        for (int i = 0; i < len; i++) {
            if (isPalin(s, 0, i)) {
                dp[i] = 0;
            } else {
                dp[i] = i;
                for (int j = 0; j < i; j++) {
                    if (dp[j] + 1 < dp[i] && isPalin(s, j + 1, i)) {
                        dp[i] = dp[j] + 1;
                    }
                }
            }
        }
        if (t++) cout << "\n";
        cout << "Partition #" << t << ":\n";
        cout << "The minimum number of partitions is " << dp[len - 1] << ".\n";
    }
    return 0;
}
