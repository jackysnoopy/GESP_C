#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000005;
int h[MAXN];
int l, t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> l >> t;
    
    for (int i = 0; i < t; i++) {
        cin >> h[i];
    }
    
    vector<int> ans;
    
    for (int start = 0; start <= t - l; start++) {
        // Current window: [start, start+l-1]
        priority_queue<int> pq;
        
        for (int i = start; i < start + l; i++) {
            if (h[i] > 0) {
                pq.push(h[i]);
            }
        }
        
        int total = 0;
        int hits = 0;
        
        // Greedy: always hit the highest mole
        while (!pq.empty() && hits < l) {
            int top = pq.top();
            pq.pop();
            
            total += top;
            hits++;
            
            if (top - 1 > 0) {
                pq.push(top - 1);
            }
        }
        
        ans.push_back(total);
    }
    
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i + 1 == ans.size() ? "\n" : " ");
    }
    
    return 0;
}