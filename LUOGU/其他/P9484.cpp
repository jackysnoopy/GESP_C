#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int k;
    cin >> s >> k;
    // Remove k digits to get smallest number
    // Greedy: use stack
    string ans;
    for (char c : s) {
        while (!ans.empty() && k > 0 && ans.back() > c) {
            ans.pop_back();
            k--;
        }
        ans.push_back(c);
    }
    while (k > 0 && !ans.empty()) { ans.pop_back(); k--; }
    // Remove leading zeros
    int start = 0;
    while (start < (int)ans.size() && ans[start] == '0') start++;
    if (start >= (int)ans.size()) cout << "0";
    else cout << ans.substr(start);
    cout << "\n";
    return 0;
}
