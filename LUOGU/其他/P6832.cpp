#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    // The most frequent non-empty substring.
    // Key insight: the most frequent substring is always a single character.
    // Proof: any substring of length L appearing k times implies each of its
    // characters appears at least k times. A single character is also a substring,
    // so max single-char frequency >= max any-substring frequency.
    // Since single-char substrings ARE substrings, they achieve the maximum.
    int cnt[26] = {};
    for (int i = 0; i < (int)s.size(); i++) cnt[s[i] - 'a']++;
    int ans = 0;
    for (int i = 0; i < 26; i++) ans = max(ans, cnt[i]);
    cout << ans << "\n";
    return 0;
}
