#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment {
    int start, end, cost;
};

bool cmp(const Segment& a, const Segment& b) {
    return a.end < b.end;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Segment> segs(n);
        for (int i = 0; i < n; i++) {
            cin >> segs[i].start >> segs[i].end >> segs[i].cost;
            if (segs[i].start > segs[i].end) swap(segs[i].start, segs[i].end);
        }
        
        int L, R;
        cin >> L >> R;
        
        sort(segs.begin(), segs.end(), cmp);
        
        vector<int> dp(R + 1, 1e9);
        dp[L] = 0;
        
        for (int i = L; i <= R; i++) {
            if (dp[i] == 1e9) continue;
            for (auto& seg : segs) {
                if (seg.start >= i && seg.end <= R) {
                    dp[seg.end] = min(dp[seg.end], dp[i] + seg.cost);
                }
            }
        }
        
        if (dp[R] == 1e9) {
            cout << -1 << endl;
        } else {
            cout << dp[R] << endl;
        }
    }
    return 0;
}
