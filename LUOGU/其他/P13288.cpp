#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        long long A;
        int N;
        cin >> A >> N;
        vector<long long> m(N);
        for (int i = 0; i < N; i++) cin >> m[i];
        sort(m.begin(), m.end());
        int ans = N; // remove all
        for (int rem = 0; rem <= N; rem++) {
            // remove last 'rem' elements, try to absorb the rest
            long long sz = A;
            int ops = rem;
            bool ok = true;
            for (int i = 0; i < N - rem; i++) {
                while (sz <= m[i]) {
                    sz += sz - 1;
                    ops++;
                    if (ops > N) break;
                }
                if (ops > N) { ok = false; break; }
                sz += m[i];
            }
            if (ok) ans = min(ans, ops);
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
