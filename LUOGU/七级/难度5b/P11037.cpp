#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }

    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; i++) {
        intervals[i] = {l[i], r[i]};
    }
    sort(intervals.begin(), intervals.end());

    vector<long long> prefix_l(n + 1, 0), prefix_r(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_l[i + 1] = prefix_l[i] + intervals[i].first;
        prefix_r[i + 1] = prefix_r[i] + intervals[i].second;
    }

    long long inv_n = power(n, MOD - 2, MOD);
    long long inv_n2 = inv_n * inv_n % MOD;

    while (q--) {
        long long x;
        cin >> x;

        long long R = x - prefix_l[n];
        if (R == 0) {
            long long sum_a2 = 0;
            for (int i = 0; i < n; i++) {
                long long v = intervals[i].first;
                sum_a2 = (sum_a2 + v * v) % MOD;
            }
            long long ans = (n % MOD * sum_a2 % MOD - (x % MOD) * (x % MOD) % MOD + MOD) % MOD;
            ans = ans * inv_n2 % MOD;
            cout << ans << "\n";
            continue;
        }

        vector<long long> a(n);
        for (int i = 0; i < n; i++) a[i] = intervals[i].first;

        for (int i = 0; i < n && R > 0; i++) {
            long long can_add = min(R, (long long)(intervals[i].second - intervals[i].first));
            a[i] += can_add;
            R -= can_add;
        }

        long long sum_a2 = 0;
        for (int i = 0; i < n; i++) {
            a[i] %= MOD;
            sum_a2 = (sum_a2 + a[i] * a[i]) % MOD;
        }

        long long x_mod = x % MOD;
        long long ans = (n % MOD * sum_a2 % MOD - x_mod * x_mod % MOD + MOD) % MOD;
        ans = ans * inv_n2 % MOD;
        cout << ans << "\n";
    }

    return 0;
}
