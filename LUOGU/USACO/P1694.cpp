#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
vector<pair<int,int>> cows;
string ans;
bool ok;

void dfs(int pos, string& s) {
    if (ok) return;
    if (pos > n) {
        for (int i = 0; i < m; i++) {
            if (s[cows[i].first] == s[cows[i].second]) return;
        }
        ans = s;
        ok = true;
        return;
    }
    for (char c = '1'; c <= '4'; c++) {
        s[pos] = c;
        bool valid = true;
        for (int i = 0; i < m && valid; i++) {
            if (pos == cows[i].first && s[cows[i].second] == c) valid = false;
            if (pos == cows[i].second && s[cows[i].first] == c) valid = false;
        }
        if (valid) dfs(pos + 1, s);
        if (ok) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    cows.resize(m);
    for (int i = 0; i < m; i++) { cin >> cows[i].first >> cows[i].second; }
    ok = false;
    string s(n + 1, '0');
    dfs(1, s);
    cout << ans.substr(1) << "\n";
    return 0;
}
