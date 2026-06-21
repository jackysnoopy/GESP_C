#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // All operations are monotone non-decreasing.
    // So max/min reachable in k ops from v is obtained by applying
    // the best/worst operation to the max/min from k-1 ops.
    vector<long long> bestMax(m + 1, (long long)-1e18);
    vector<long long> bestMax2(m + 1, (long long)-1e18);
    vector<int> bestMaxIdx(m + 1, -1);
    vector<long long> bestMin(m + 1, (long long)1e18);
    vector<long long> bestMin2(m + 1, (long long)1e18);
    vector<int> bestMinIdx(m + 1, -1);

    for (int i = 0; i < n; i++) {
        long long mx[11], mn[11];
        mx[0] = a[i];
        mn[0] = a[i];
        for (int k = 1; k <= m; k++) {
            mx[k] = max(mx[k - 1] + 2, max(mx[k - 1] - 2, max(mx[k - 1] * 2, mx[k - 1] / 2)));
            mn[k] = min(mn[k - 1] + 2, min(mn[k - 1] - 2, min(mn[k - 1] * 2, mn[k - 1] / 2)));
        }
        for (int k = 0; k <= m; k++) {
            if (mx[k] > bestMax[k]) {
                bestMax2[k] = bestMax[k];
                bestMax[k] = mx[k];
                bestMaxIdx[k] = i;
            } else if (mx[k] > bestMax2[k] && i != bestMaxIdx[k]) {
                bestMax2[k] = mx[k];
            }
            if (mn[k] < bestMin[k]) {
                bestMin2[k] = bestMin[k];
                bestMin[k] = mn[k];
                bestMinIdx[k] = i;
            } else if (mn[k] < bestMin2[k] && i != bestMinIdx[k]) {
                bestMin2[k] = mn[k];
            }
        }
    }

    long long ans = (long long)-4e18;
    for (int k = 0; k <= m; k++) {
        int mk = m - k;
        long long mx, mn;
        if (bestMaxIdx[k] != bestMinIdx[mk]) {
            mx = bestMax[k];
            mn = bestMin[mk];
        } else {
            mx = bestMax[k];
            mn = bestMin[mk];
            if (bestMax2[k] - bestMin[mk] > mx - mn) {
                mx = bestMax2[k];
            }
            if (bestMax[k] - bestMin2[mk] > mx - mn) {
                mx = bestMax[k];
                mn = bestMin2[mk];
            }
        }
        ans = max(ans, mx - mn);
    }

    cout << ans << endl;
    return 0;
}
