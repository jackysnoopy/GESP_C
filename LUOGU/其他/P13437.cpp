#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string s;
        cin >> s;
        map<char, int> cnt;
        for (char c : s) cnt[c]++;
        // Assign digits: first distinct char -> 1, second -> 0, rest -> 2,3,...
        string order;
        for (auto& p : cnt) order += p.first;
        map<char, int> val;
        if (!order.empty()) val[order[0]] = 1;
        if (order.size() > 1) val[order[1]] = 0;
        int v = 2;
        for (int i = 2; i < (int)order.size(); i++) {
            val[order[i]] = v++;
        }
        long long base = cnt.size();
        long long result = 0;
        for (char c : s) {
            result = result * base + val[c];
        }
        cout << "Case #" << tc << ": " << result << "\n";
    }
    return 0;
}
