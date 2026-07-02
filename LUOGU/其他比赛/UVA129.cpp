#include <iostream>
#include <string>
#include <functional>
using namespace std;

int n, k;
int cnt;

bool check(const string& s, int len) {
    int slen = s.size();
    if (slen < 2 * len) return true;
    for (int i = slen - 2 * len; i < slen - len; i++) {
        bool ok = false;
        for (int j = 0; j < len; j++) {
            if (s[i + j] != s[i + len + j]) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    function<void(string&, int)> dfs = [&](string& s, int depth) {
        if (cnt >= k) return;
        if (depth == n) {
            cnt++;
            if (cnt == k) {
                for (int i = 0; i < n; i++) {
                    if (i > 0 && i % 4 == 0) cout << " ";
                    cout << s[i];
                }
                cout << "\n";
            }
            return;
        }
        for (char c = 'A'; c <= 'C'; c++) {
            s.push_back(c);
            if (check(s, 1) && check(s, 2)) {
                dfs(s, depth + 1);
            }
            s.pop_back();
            if (cnt >= k) return;
        }
    };
    
    while (cin >> n >> k && (n != 0 || k != 0)) {
        cnt = 0;
        string s;
        dfs(s, 0);
    }
    
    return 0;
}
