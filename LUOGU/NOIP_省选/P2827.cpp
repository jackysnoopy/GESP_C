#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.rbegin(), a.rend());
    
    queue<int> q1, q2, q3;
    for (int x : a) q1.push(x);
    
    int delta = 0;
    
    auto get_max = [&]() {
        int val = -1e9;
        if (!q1.empty()) val = max(val, q1.front());
        if (!q2.empty()) val = max(val, q2.front());
        if (!q3.empty()) val = max(val, q3.front());
        if (!q1.empty() && q1.front() == val) { q1.pop(); return val; }
        if (!q2.empty() && q2.front() == val) { q2.pop(); return val; }
        if (!q3.empty() && q3.front() == val) { q3.pop(); return val; }
        return val;
    };
    
    for (int i = 1; i <= m; i++) {
        int len = get_max() + delta;
        if (i % t == 0) cout << len << (i + t <= m ? " " : "");
        
        int len1 = (long long)len * u / v;
        int len2 = len - len1;
        delta += q;
        q2.push(len1 - delta);
        q3.push(len2 - delta);
    }
    cout << "\n";
    
    vector<int> result;
    while (!q1.empty() || !q2.empty() || !q3.empty())
        result.push_back(get_max() + delta);
    for (int i = 0; i < (int)result.size(); i++)
        if ((i + 1) % t == 0)
            cout << result[i] << (i + t < (int)result.size() ? " " : "");
    cout << "\n";
    
    return 0;
}