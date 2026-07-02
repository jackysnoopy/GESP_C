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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), greater<long long>());

    long long sum_sq = 0;
    for (int i = 0; i < n; i++) {
        sum_sq += a[i] * a[i];
    }

    vector<long long> ans(n + 1, sum_sq);

    for (int g = 1; g < n; g++) {
        if (n % g != 0) continue;
        int L = n / g;
        long long total = 0;

        for (int cyc = 0; cyc < g; cyc++) {
            int base = cyc * L;
            if (L == 1) continue;

            vector<int> idx;
            for (int i = 0; i < L; i += 2) idx.push_back(i);
            for (int i = L - 1 - (L % 2); i >= 1; i -= 2) idx.push_back(i);

            for (int i = 0; i < L; i++) {
                total += a[base + idx[i]] * a[base + idx[(i + 1) % L]];
            }
        }
        ans[g] = total;
    }

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        if (k == 0) {
            cout << sum_sq << "\n";
        } else {
            int g = n, tk = k;
            while (tk) { int t = g % tk; g = tk; tk = t; }
            cout << ans[g] << "\n";
        }
    }

    return 0;
}
