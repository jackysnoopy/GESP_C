#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long W;
    int N;
    if (!(cin >> W >> N)) return 0;
    vector<long long> g(N);
    for (int i = 0; i < N; ++i) cin >> g[i];
    sort(g.begin(), g.end(), greater<long long>());

    int n1 = N / 2;
    int n2 = N - n1;
    vector<long long> left;
    left.reserve(1 << n1);
    for (int mask = 0; mask < (1 << n1); ++mask) {
        long long s = 0;
        for (int i = 0; i < n1; ++i) if (mask & (1 << i)) s += g[i];
        if (s <= W) left.push_back(s);
    }
    sort(left.begin(), left.end());

    long long ans = 0;
    for (int mask = 0; mask < (1 << n2); ++mask) {
        long long s = 0;
        for (int i = 0; i < n2; ++i) if (mask & (1 << i)) s += g[n1 + i];
        if (s > W) continue;
        long long rem = W - s;
        auto it = upper_bound(left.begin(), left.end(), rem);
        if (it != left.begin()) {
            --it;
            ans = max(ans, s + *it);
        } else {
            ans = max(ans, s);
        }
    }
    cout << ans << '\n';
    return 0;
}
