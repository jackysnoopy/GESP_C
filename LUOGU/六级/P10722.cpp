#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> children(n + 1);
    for (int v = 2; v <= n; v++) {
        int p;
        cin >> p;
        children[p].push_back(v);
    }
    
    string color_str;
    cin >> color_str;
    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) {
        color[i] = color_str[i - 1] - '0';
    }
    
    // DFS 序
    vector<int> in(n + 1), out(n + 1), pos(n + 1);
    int timer = 0;
    function<void(int)> dfs = [&](int u) {
        in[u] = ++timer;
        pos[timer] = u;
        for (int v : children[u]) {
            dfs(v);
        }
        out[u] = timer;
    };
    dfs(1);
    
    // 差分数组
    vector<int> diff(n + 5, 0);
    int q;
    cin >> q;
    while (q--) {
        int a;
        cin >> a;
        diff[in[a]]++;
        diff[out[a] + 1]--;
    }
    
    // 前缀和 + 输出
    int cur = 0;
    string ans(n, '0');
    for (int t = 1; t <= n; t++) {
        cur += diff[t];
        int u = pos[t];
        int fc = color[u] ^ (cur & 1);
        ans[u - 1] = '0' + fc;
    }
    
    cout << ans << "\n";
    return 0;
}
