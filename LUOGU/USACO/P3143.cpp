#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    // For each left end i, find max right end j where a[j]-a[i] <= k
    vector<int> right(n);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && a[j] - a[i] <= k) j++;
        right[i] = j - i; // max diamonds from i
    }
    // Suffix max of right[i]: best we can do from position i onward
    vector<int> suf(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) suf[i] = max(suf[i + 1], right[i]);
    // For each left case, combine with best right case
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int left = right[i];
        int rightBest = (i + left < n) ? suf[i + left] : 0;
        ans = max(ans, left + rightBest);
    }
    cout << ans << "\n";
    return 0;
}
