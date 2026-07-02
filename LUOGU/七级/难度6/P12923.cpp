#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    
    // Z-algorithm 或 KMP 找所有可能的模板长度
    // 模板和其反向可以拼出原串
    
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    
    vector<int> ans;
    for (int len = 1; len <= n; len++) {
        // 检查长度 len 是否可行
        bool ok = true;
        for (int i = 0; i + len <= n; i += len) {
            int remaining = min(len, n - i);
            if (z[i] < remaining && i + len < n) {
                ok = false;
                break;
            }
        }
        if (ok) ans.push_back(len);
    }
    
    for (int i = 0; i < ans.size(); i++) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    
    return 0;
}
