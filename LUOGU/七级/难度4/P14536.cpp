#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    vector<int> a(m), b(m), l(m);
    for (int i = 0; i < m; i++) cin >> a[i] >> b[i] >> l[i];

    vector<int> road_cap = l;
    int ans = 0;

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int x, int y) {
        return h[x] > h[y];
    });

    for (int i : order) {
        int best_road = -1;
        for (int j = 0; j < m; j++) {
            if ((a[j] == i || b[j] == i) && road_cap[j] >= h[i]) {
                if (best_road == -1 || road_cap[j] > road_cap[best_road]) {
                    best_road = j;
                }
            }
        }
        if (best_road != -1) {
            road_cap[best_road] -= h[i];
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
