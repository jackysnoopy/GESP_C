#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
    vector<char> ans(n, 'N');
    long long sum = a[idx[0]];
    for (int k = 1; k < n; ++k) {
        int pos = idx[k];
        if (a[pos] <= sum) ans[pos] = 'T';
        sum += a[pos];
    }
    for (int i = 0; i < n; ++i) cout << ans[i];
    cout << '\n';
    return 0;
}
