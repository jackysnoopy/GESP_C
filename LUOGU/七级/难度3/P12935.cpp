#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Balls of Buma：球的最大数量
    // 简化问题：找最大连续相同数
    int maxLen = 1, curLen = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            curLen++;
        } else {
            curLen = 1;
        }
        maxLen = max(maxLen, curLen);
    }

    cout << maxLen << "\n";

    return 0;
}
