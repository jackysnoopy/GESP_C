#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    vector<int> pos(n+1);
    for (int i = 0; i < n; i++) pos[sorted_a[i]] = i;
    vector<bool> vis(n, false);
    long long ans = 0;
    int globalMin = *min_element(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        if (vis[i] || a[i] == sorted_a[i]) continue;
        int cur = i;
        long long cycleSum = 0, cycleMin = 1e9, cycleLen = 0;
        while (!vis[cur]) {
            vis[cur] = true;
            cycleSum += a[cur];
            cycleMin = min(cycleMin, (long long)a[cur]);
            cycleLen++;
            cur = pos[a[cur]];
        }
        long long method1 = cycleSum + cycleMin * (cycleLen - 2);
        long long method2 = cycleSum + cycleMin + globalMin * 2 + globalMin * (cycleLen - 1);
        ans += min(method1, method2);
    }
    cout << ans << endl;
    return 0;
}