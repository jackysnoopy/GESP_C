#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    int cnt = N + M + 1;
    vector<long long> a(cnt);
    for (int i = 0; i < cnt; ++i) cin >> a[i];
    sort(a.begin(), a.end());
    if (M == 0) {
        long long ans = 0;
        for (long long x : a) ans += x;
        cout << ans << '\n';
        return 0;
    }
    long long ans = 0;
    ans += a[cnt - 1];
    ans -= a[0];
    for (int i = 1; i <= M; ++i) ans += abs(a[i]);
    for (int i = M + 1; i < cnt - 1; ++i) ans += a[i];
    cout << ans << '\n';
    return 0;
}
