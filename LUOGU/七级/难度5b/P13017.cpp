#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> deg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        deg[u]++;
        deg[v]++;
    }
    long long ans = 0;
    for (int i = 0; i < n; i++)
        ans += 1LL * deg[i] * (deg[i] - 1) / 2;
    cout << ans << "\n";
    return 0;
}
