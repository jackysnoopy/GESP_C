#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    vector<int> cnt(26, 0);
    for (char c : s) cnt[c - 'a']++;
    int best = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > cnt[best]) best = i;
    }
    string result = "";
    for (int i = 0; i < cnt[best]; i++) result += (char)('a' + best);
    cout << result << "\n";
    return 0;
}
