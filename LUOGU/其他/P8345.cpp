#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c, q;
    cin >> n >> c >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    while (q--) {
        int sz;
        cin >> sz;
        vector<long long> S(sz);
        for (int i = 0; i < sz; i++) cin >> S[i];
        sort(S.begin(), S.end(), [&](int i, int j) { return a[i-1] < a[j-1]; });
        long long ans = 0;
        for (int i = 1; i < sz; i++) {
            int u = S[i-1] - 1, v = S[i] - 1;
            ans += a[u] - 2 * a[v] + c;
        }
        cout << ans << "\n";
    }
    return 0;
}
