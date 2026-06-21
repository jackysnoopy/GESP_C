#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> p(m);
    for (int i = 0; i < m; i++) cin >> p[i];
    vector<long long> cnt(n + 2, 0);
    for (int i = 0; i + 1 < m; i++) {
        int l = p[i], r = p[i + 1];
        if (l > r) swap(l, r);
        cnt[l]++; cnt[r]--;
    }
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i-1];
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        long long A, B, C;
        cin >> A >> B >> C;
        ans += min(cnt[i] * A, cnt[i] * B + C);
    }
    cout << ans << "\n";
    return 0;
}
