#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    vector<int> min_suf(n + 2, INT_MAX);
    for (int i = n; i >= 1; i--)
        min_suf[i] = min(min_suf[i+1], a[i]);
    
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (a[i] < a[j] && min_suf[j+1] < a[i])
                g[i].push_back(j), g[j].push_back(i);
    
    vector<int> color(n + 1, -1);
    function<bool(int)> dfs = [&](int u) {
        for (int v : g[u]) {
            if (color[v] == -1) {
                color[v] = color[u] ^ 1;
                if (!dfs(v)) return false;
            } else if (color[v] == color[u]) {
                return false;
            }
        }
        return true;
    };
    
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            if (!dfs(i)) { cout << "0\n"; return 0; }
        }
    }
    
    stack<int> s1, s2;
    string ans;
    int cur = 1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            ans += "a ";
            s1.push(a[i]);
        } else {
            ans += "c ";
            s2.push(a[i]);
        }
        while (!s1.empty() && s1.top() == cur) { s1.pop(); ans += "b "; cur++; }
        while (!s2.empty() && s2.top() == cur) { s2.pop(); ans += "d "; cur++; }
    }
    
    cout << ans << "\n";
    return 0;
}