#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> s(n), a(n), e(n);
    for (int i = 0; i < n; ++i) cin >> s[i] >> a[i] >> e[i];
    vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
    long long t = 0, ans = 0;
    for (int id : idx) {
        t += s[id];
        ans += t + a[id];
        t += e[id];
    }
    cout << ans << '\n';
    return 0;
}
