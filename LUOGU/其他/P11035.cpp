#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long p;
    cin >> n >> p;
    vector<long long> a(n);
    long long sum_pos = 0;
    long long mn_neg = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) sum_pos += a[i];
        if (a[i] < 0) mn_neg = min(mn_neg, a[i]);
    }
    long long ans = p + 2 * sum_pos;
    if (sum_pos > 0) ans += mn_neg;
    cout << ans << "\n";
    return 0;
}
