#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    
    vector<int> a_times(m1), b_times(m2);
    for (int i = 0; i < m1; i++) {
        cin >> a_times[i];
    }
    for (int i = 0; i < m2; i++) {
        cin >> b_times[i];
    }
    
    // Sort machines by time (fastest first)
    sort(a_times.begin(), a_times.end());
    sort(b_times.begin(), b_times.end());
    
    // Calculate time for A operations
    int time_a = 0;
    priority_queue<int, vector<int>, greater<int>> pq_a;
    for (int t : a_times) {
        pq_a.push(0);
    }
    
    for (int i = 0; i < n; i++) {
        int earliest = pq_a.top();
        pq_a.pop();
        pq_a.push(earliest + a_times[i % m1]);
    }
    
    time_a = pq_a.top();
    
    // Calculate time for B operations
    int time_b = 0;
    priority_queue<int, vector<int>, greater<int>> pq_b;
    for (int t : b_times) {
        pq_b.push(0);
    }
    
    for (int i = 0; i < n; i++) {
        int earliest = pq_b.top();
        pq_b.pop();
        pq_b.push(earliest + b_times[i % m2]);
    }
    
    time_b = pq_b.top();
    
    cout << time_a << " " << time_a + time_b << "\n";
    return 0;
}
