#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Find two disjoint intervals with max sum
    // prefix max and suffix max approach
    vector<long long> pre(n), suf(n);
    // pre[i] = max subarray sum in a[0..i]
    long long best = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
        pre[i] = best;
    }
    best = 0; cur = 0;
    for (int i = n-1; i >= 0; i--) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
        suf[i] = best;
    }
    // Two disjoint: pre[i] + suf[i+1] for some i
    long long ans = 0;
    for (int i = 0; i < n-1; i++) {
        ans = max(ans, pre[i] + suf[i+1]);
    }
    cout << ans << "\n";
    return 0;
}
