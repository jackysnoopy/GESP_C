#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<pair<long long,long long>> seg(M);
    for (int i = 0; i < M; i++) {
        cin >> seg[i].first >> seg[i].second;
    }
    sort(seg.begin(), seg.end());
    long long lo = 1, hi = 2e18;
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        long long prev = seg[0].first;
        int cnt = 1;
        for (int i = 0; i < M; i++) {
            long long start = max(seg[i].first, prev);
            while (start + mid <= seg[i].second) {
                start += mid;
                cnt++;
                if (cnt >= N) break;
            }
            if (cnt >= N) break;
            prev = start + mid;
        }
        if (cnt >= N) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
