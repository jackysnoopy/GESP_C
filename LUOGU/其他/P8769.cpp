#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// [蓝桥杯 2021 国 C] 巧克力
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, n;
    cin >> x >> n;
    vector<pair<int, pair<long long, long long>>> choco(n);
    for (int i = 0; i < n; i++) {
        cin >> choco[i].second.first >> choco[i].first >> choco[i].second.second;
    }
    sort(choco.begin(), choco.end());
    
    typedef pair<long long, int> PLI;
    priority_queue<PLI, vector<PLI>, greater<PLI>> pq;
    long long cost = 0;
    int idx = n - 1;
    bool possible = true;
    
    for (int day = x; day >= 1; day--) {
        while (idx >= 0 && choco[idx].first >= day) {
            pq.push(PLI(choco[idx].second.first, (int)choco[idx].second.second));
            idx--;
        }
        if (pq.empty()) {
            possible = false;
            break;
        }
        PLI top = pq.top();
        pq.pop();
        cost += top.first;
        top.second--;
        if (top.second > 0) pq.push(top);
    }
    
    if (possible) cout << cost << "\n";
    else cout << "-1\n";
    return 0;
}
