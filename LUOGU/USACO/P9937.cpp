#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, l;
    cin >> n >> l;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    sort(c.begin(), c.end(), greater<int>());
    // h-index: max h such that at least h papers have >= h citations
    // With L extra citations (each +1 to a different paper)
    // Binary search on h. For target h:
    // Count papers with >= h citations: cnt.
    // If cnt >= h: feasible (need 0 extra).
    // Else need h-cnt extra citations (raise h-cnt papers from <h to >=h).
    // But each paper can only get +1, so a paper with h-1 citations can become h.
    // Papers with < h-1 citations can't reach h with just +1.
    // So: count how many papers have c[i] >= h: cnt1
    // Count how many papers have c[i] == h-1: cnt2
    // Can raise min(cnt2, h-cnt1) papers.
    // Feasible if cnt1 + min(cnt2, h-cnt1) >= h and total extra <= L.
    // Actually: extra needed = max(0, h - cnt1). But only papers with c[i] >= h-1 can reach h.
    // So: extra_needed = max(0, h - cnt1) but must be <= cnt2 and <= L.
    
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; i++) {
            if (c[i] >= mid) cnt1++;
            else if (c[i] == mid - 1) cnt2++;
        }
        int extra = max(0, mid - cnt1);
        if (extra <= cnt2 && extra <= l) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo << "\n";
    return 0;
}
