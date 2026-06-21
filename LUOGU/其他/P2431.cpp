#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long m;
    cin >> n >> m;
    vector<long long> w(n), s(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> s[i];
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b){ return w[a]+s[a] < w[b]+s[b]; });
    long long sum = 0, ans = -1e18;
    for (int i = 0; i < n; i++) {
        ans = max(ans, sum - s[idx[i]]);
        sum += w[idx[i]];
    }
    cout << ans << "\n";
    return 0;
}
