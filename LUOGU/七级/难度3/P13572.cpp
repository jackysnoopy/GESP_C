#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        deg[x]++; deg[y]++;
    }
    if (n == 1) { printf("%d\n", a[1]); return 0; }
    vector<pair<int,int>> vals;
    for (int i = 1; i <= n; i++) vals.push_back({a[i], deg[i]});
    sort(vals.begin(), vals.end(), greater<pair<int,int>>());
    int ans = 0;
    int count_ge = 0, count_ge_deg2 = 0;
    int idx = 0;
    while (idx < n) {
        int v = vals[idx].first;
        int start = idx;
        while (idx < n && vals[idx].first == v) {
            count_ge++;
            if (vals[idx].second >= 2) count_ge_deg2++;
            idx++;
        }
        if (count_ge >= 2 || count_ge_deg2 >= 1) { ans = v; break; }
    }
    printf("%d\n", ans);
    return 0;
}
