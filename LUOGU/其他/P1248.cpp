#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// P1248: 加工生产调度
// n jobs, 2 machines. Minimize makespan (Johnson's algorithm).
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    // Johnson's algorithm
    vector<pair<int,int>> jobs(n);
    for (int i = 0; i < n; i++) jobs[i] = {i, i};
    sort(jobs.begin(), jobs.end(), [&](const pair<int,int>& x, const pair<int,int>& y) {
        return a[x.second] < b[y.second];
    });
    
    vector<int> order;
    int lo = 0, hi = n - 1;
    for (int i = 0; i < n; i++) {
        if (a[jobs[i].second] <= b[jobs[i].second]) {
            order.insert(order.begin() + lo++, jobs[i].second);
        } else {
            order.insert(order.begin() + hi--, jobs[i].second);
        }
    }
    
    int time1 = 0, time2 = 0;
    for (int i = 0; i < n; i++) {
        time1 += a[order[i]];
        time2 = max(time2, time1) + b[order[i]];
    }
    
    cout << time2 << "\n";
    for (int i = 0; i < n; i++) {
        cout << order[i] + 1 << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
