#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n);
    vector<long long> b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    vector<int> have(k + 1, 0);
    for (int i = 0; i < n; ++i) if (1 <= a[i] && a[i] <= k) have[a[i]]++;
    int need = 0;
    for (int i = 1; i <= k; ++i) if (!have[i]) ++need;
    if (need == 0) {
        cout << 0 << '\n';
        return 0;
    }
    vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) { return b[i] < b[j]; });
    long long ans = 0;
    for (int id : idx) {
        if (need <= 0) break;
        if (1 <= a[id] && a[id] <= k && have[a[id]] > 1) {
            --have[a[id]];
            --need;
            ans += b[id];
        }
    }
    for (int id : idx) {
        if (need <= 0) break;
        --need;
        ans += b[id];
    }
    cout << ans << '\n';
    return 0;
}
