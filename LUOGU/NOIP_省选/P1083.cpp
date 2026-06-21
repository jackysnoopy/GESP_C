#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> r(n + 1);
    for (int i = 1; i <= n; i++) cin >> r[i];
    vector<int> d(m + 1), s(m + 1), t(m + 1);
    for (int i = 1; i <= m; i++) cin >> d[i] >> s[i] >> t[i];
    auto check = [&](int mid) -> bool {
        vector<long long> diff(n + 2, 0);
        for (int i = 1; i <= mid; i++) {
            diff[s[i]] += d[i];
            diff[t[i] + 1] -= d[i];
        }
        long long cur = 0;
        for (int i = 1; i <= n; i++) {
            cur += diff[i];
            if (cur > r[i]) return false;
        }
        return true;
    };
    int lo = 0, hi = m;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    if (lo == m) cout << "0\n";
    else cout << "-1\n" << lo + 1 << "\n";
    return 0;
}
