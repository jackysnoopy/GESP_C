#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W, k;
    cin >> n >> W >> k;

    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int x, int y) {
        return (double)v[x] / w[x] > (double)v[y] / w[y];
    });

    long long ans = 0;
    int used = 0;
    int budget = W;

    for (int i = 0; i < n && used < n; i++) {
        int idx = order[i];
        if (used < k) {
            ans += v[idx];
            used++;
        } else if (budget >= w[idx]) {
            ans += v[idx];
            budget -= w[idx];
            used++;
        }
    }

    cout << ans << "\n";
    return 0;
}
