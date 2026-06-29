#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> jobs(n);
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].first >> jobs[i].second;
    }
    
    // Sort jobs by deadline
    sort(jobs.begin(), jobs.end());
    
    // Use a min-heap to track selected jobs
    priority_queue<int, vector<int>, greater<int>> pq;
    long long total_profit = 0;
    
    for (int i = 0; i < n; i++) {
        int deadline = jobs[i].first;
        int profit = jobs[i].second;
        
        if (pq.size() < deadline) {
            pq.push(profit);
            total_profit += profit;
        } else if (pq.top() < profit) {
            total_profit -= pq.top();
            pq.pop();
            pq.push(profit);
            total_profit += profit;
        }
    }
    
    cout << total_profit << "\n";
    return 0;
}
