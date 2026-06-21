#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int cnt[26] = {0};
    for (char c : s) cnt[c - 'a']++;
    int l = cnt['l' - 'a'];
    int q = cnt['q' - 'a'];
    int b = cnt['b' - 'a'];
    cout << min(l, min(q, b)) << "\n";
    return 0;
}
