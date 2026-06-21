#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, T;
    cin >> n >> T;
    vector<pair<int,int>> segs(n);
    for (int i = 0; i < n; i++) cin >> segs[i].first >> segs[i].second;
    sort(segs.begin(), segs.end());
    
    int ans = 0, cur = 0, idx = 0;
    while (cur < T) {
        int best = cur;
        while (idx < n && segs[idx].first <= cur + 1) {
            best = max(best, segs[idx].second);
            idx++;
        }
        if (best == cur) { cout << -1 << "\n"; return 0; }
        cur = best;
        ans++;
    }
    cout << ans << "\n";
    return 0;
}
