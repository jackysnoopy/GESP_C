#include <iostream>
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
    vector<int> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    
    vector<int> h(n + 1, 0);
    vector<bool> full(n + 1, false), ok(n + 1, false);
    int ans = 0;
    
    function<void(int)> dfs = [&](int u) {
        if (u == 0) return;
        dfs(l[u]);
        dfs(r[u]);
        
        int hl = h[l[u]], hr = h[r[u]];
        bool fl = (l[u] == 0) || full[l[u]];
        bool fr = (r[u] == 0) || full[r[u]];
        bool cl = (l[u] == 0) || ok[l[u]];
        bool cr = (r[u] == 0) || ok[r[u]];
        
        h[u] = max(hl, hr) + 1;
        full[u] = fl && fr && (hl == hr);
        ok[u] = cl && cr && 
                ((hl == hr && fl) || (hl == hr + 1 && fr));
        
        if (ok[u]) ans++;
    };
    dfs(1);
    
    cout << ans << "\n";
    return 0;
}
