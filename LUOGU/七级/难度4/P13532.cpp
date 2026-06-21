#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> shops(n);
    for (int i = 0; i < n; i++) {
        cin >> shops[i].first >> shops[i].second;
    }

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int x, int y) {
        return shops[x].first < shops[y].first;
    });

    int ans = 1e9;
    int max_b = 0;

    for (int i = 0; i < n; i++) {
        int idx = order[i];
        max_b = max(max_b, shops[idx].second);
        if (i < n - 1) {
            int next_a = shops[order[i + 1]].first;
            ans = min(ans, abs(max_b - next_a));
        }
    }

    cout << ans << "\n";
    return 0;
}
