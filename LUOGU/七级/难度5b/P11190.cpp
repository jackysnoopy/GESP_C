#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, q;
    cin >> c >> q;

    while (q--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> cnt(26, 0);
        for (char ch : s) cnt[ch - 'a']++;

        int maxcnt = *max_element(cnt.begin(), cnt.end());

        if (maxcnt == n) {
            cout << "Shuiniao\n";
            continue;
        }

        vector<vector<int>> groups;
        vector<int> cur;
        vector<bool> used(n, false);

        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                cur.clear();
                cur.push_back(i);
                used[i] = true;
                for (int j = i + 1; j < n; j++) {
                    if (!used[j] && s[j] != s[i]) {
                        cur.push_back(j);
                        used[j] = true;
                        break;
                    }
                }
                if (cur.size() == 1) {
                    for (int j = 0; j < n; j++) {
                        if (!used[j]) {
                            cur.push_back(j);
                            used[j] = true;
                            break;
                        }
                    }
                }
                if (cur.size() >= 2) {
                    bool ok = true;
                    if (cur.size() == 2 && s[cur[0]] == s[cur[1]]) ok = false;
                    if (cur.size() > 2) {
                        int len = cur.size();
                        bool is_pal = true;
                        for (int k = 0; k < len / 2; k++) {
                            if (s[cur[k]] != s[cur[len - 1 - k]]) {
                                is_pal = false;
                                break;
                            }
                        }
                        if (is_pal) ok = false;
                    }
                    if (ok) {
                        groups.push_back(cur);
                    } else {
                        for (int idx : cur) used[idx] = false;
                    }
                }
            }
        }

        vector<int> remaining;
        for (int i = 0; i < n; i++) {
            if (!used[i]) remaining.push_back(i);
        }

        if (!remaining.empty()) {
            if (remaining.size() == 1) {
                if (!groups.empty()) {
                    groups.back().push_back(remaining[0]);
                } else {
                    cout << "Shuiniao\n";
                    continue;
                }
            } else {
                groups.push_back(remaining);
            }
        }

        bool valid = true;
        for (auto& g : groups) {
            if (g.size() == 1) { valid = false; break; }
            if (g.size() == 2 && s[g[0]] == s[g[1]]) { valid = false; break; }
            int len = g.size();
            bool is_pal = true;
            for (int k = 0; k < len / 2; k++) {
                if (s[g[k]] != s[g[len - 1 - k]]) { is_pal = false; break; }
            }
            if (is_pal && len > 1) { valid = false; break; }
        }

        if (!valid) {
            cout << "Shuiniao\n";
        } else {
            cout << "Huoyu\n";
            cout << groups.size() << "\n";
            for (auto& g : groups) {
                cout << g.size();
                for (int idx : g) cout << " " << idx + 1;
                cout << "\n";
            }
        }
    }

    return 0;
}
