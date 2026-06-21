#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> seg[i].first >> seg[i].second;
    }
    sort(seg.begin(), seg.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;
    for (int i = 0; i < k; i++) {
        pq.push(seg[i].second);
        ans = min(ans, seg[i].first);
    }
    int start = seg[0].first;
    int end = seg[k-1].second;
    cout << max(end - start, 0) << "\n";
    for (int i = 0; i < k; i++) {
        if (i > 0) cout << " ";
        cout << i + 1;
    }
    cout << "\n";
    return 0;
}
