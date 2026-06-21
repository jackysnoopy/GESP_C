#include <iostream>
#include <vector>
using namespace std;

// P1413 - No data file available. This is likely "圆的最大面积" or another classic problem.
// P1413 on Luogu is "地鼠逃跑" or "找第一个只出现一次的字符"
// Actually P1413 is "找第一个只出现一次的字符" (find first non-repeating character)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int cnt[256] = {};
    for (char c : s) cnt[(unsigned char)c]++;
    for (char c : s) {
        if (cnt[(unsigned char)c] == 1) {
            cout << c << "\n";
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}
