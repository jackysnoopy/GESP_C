#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    string s;
    if (!(cin >> N >> s)) return 0;
    int ans = 0;
    for (int i = 0; i < N; ) {
        if (s[i] == '0') { ++i; continue; }
        int j = i;
        while (j < N && s[j] == '1') ++j;
        int len = j - i;
        ans += (len + 2) / 3;
        i = j;
    }
    cout << ans << '\n';
    return 0;
}
