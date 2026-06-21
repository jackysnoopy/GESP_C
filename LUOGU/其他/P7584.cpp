#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    // Player i gets n+1-rank points. Best case: rank 1 => n points.
    // Player i can become highest if b[i] + n > max of all others' best.
    // Others best: b[j] + (n-1) for j!=i (they get 2nd place at best).
    // Actually we need b[i] + n > b[j] + (n-1-rank) for all j.
    // Easiest: sort. Player i best = b[i]+n. Others worst best = b[j]+0 for j!=i.
    // Player i can be highest iff b[i]+n > max(b[j]) for all j!=i
    // Wait: max possible for player j is b[j]+n (rank 1).
    // But only one player can be rank 1. So if i is rank 1 (gets n),
    // the best any other player j can get is b[j]+(n-1) (rank 2).
    // So player i can be highest if b[i]+n > max_{j!=i}(b[j]+(n-1))
    // = b[i]+n > max_other + n - 1
    // = b[i] > max_other - 1
    // = b[i] >= max_other
    // But if there are ties... let's sort and count.
    sort(b.begin(), b.end());
    int mx = b[n-1];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        // best for i: b[i]+n. Others best (2nd place): b[j]+(n-1) for the max j!=i
        int otherMax = (b[i] == mx) ? b[n-2] : mx;
        if (b[i] + n > otherMax + n - 1) ans++;
    }
    cout << ans << "\n";
    return 0;
}
