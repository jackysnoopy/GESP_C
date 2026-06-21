#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    double total_pairs = (double)n * (n - 1) / 2.0;
    double e_and = 0, e_or = 0, e_xor = 0;
    for (int k = 0; k < 32; ++k) {
        long long cnt = 0;
        for (int i = 0; i < n; ++i)
            if ((a[i] >> k) & 1) cnt++;
        double p_and = cnt * (cnt - 1) / 2.0 / total_pairs;
        double p_or = 1.0 - (n - cnt) * (n - cnt - 1) / 2.0 / total_pairs;
        e_and += p_and * (1LL << k);
        e_or += p_or * (1LL << k);
        e_xor += (p_or - p_and) * (1LL << k);
    }
    printf("%.3f %.3f %.3f\n", e_and, e_or, e_xor);
    return 0;
}
