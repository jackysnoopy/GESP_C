#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> c(n);
        for (int i = 0; i < n; ++i) cin >> c[i];
        int seg = 1;
        for (int i = 1; i < n; ++i) if (c[i] != c[i - 1]) ++seg;
        if (m >= k) {
            cout << n << '\n';
            continue;
        }
        vector<int> lens;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && c[j] == c[i]) ++j;
            lens.push_back(j - i);
            i = j;
        }
        long long ans = 0;
        for (int x : lens) {
            if (x == 1) {
                ans += 1;
                continue;
            }
            long long add = min((long long)m, (long long)(x - 1));
            ans += 1 + add;
            m -= (int)add;
        }
        cout << ans << '\n';
    }
    return 0;
}
