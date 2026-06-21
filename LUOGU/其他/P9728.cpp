#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a;
    if (!(cin >> n >> a)) return 0;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) cin >> b[i];
    int can = 0;
    for (int i = 0; i < n; ++i) if (b[i] == 1) ++can;
    int choose = min(can, a);
    long long base = 2LL * n * n - 2LL * n * choose + 1LL * choose * choose;
    long long ans = base;
    for (int k = 0; k <= choose; ++k) {
        long long cur = base;
        cur -= 1LL * k * (k - 1);
        cur += 1LL * k * (n - a);
        cur += 1LL * (choose - k) * (k);
        ans = max(ans, cur);
    }
    cout << ans << '\n';
    return 0;
}
