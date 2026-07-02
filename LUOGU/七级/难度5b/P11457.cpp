#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<long long, long long>> jobs(n);
        for (int i = 0; i < n; i++) {
            cin >> jobs[i].first >> jobs[i].second;
        }
        sort(jobs.begin(), jobs.end());
        priority_queue<long long> pq;
        long long curTime = 0;
        for (int i = 0; i < n; i++) {
            curTime += jobs[i].second;
            pq.push(jobs[i].second);
            if (curTime > jobs[i].first) {
                curTime -= pq.top();
                pq.pop();
            }
        }
        cout << pq.size() << "\n";
    }
    return 0;
}
