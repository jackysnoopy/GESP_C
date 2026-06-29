#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    if (m == 0) {
        cout << 0 << "\n";
        return 0;
    }
    
    if (n < 2 * m) {
        cout << "Error!\n";
        return 0;
    }
    
    // 贪心+反悔堆
    // 将环拆成链，复制一份
    vector<int> b(2 * n);
    for (int i = 0; i < n; i++) {
        b[i] = b[i + n] = a[i];
    }
    
    // 使用堆维护可选位置
    priority_queue<pair<int, int>> pq;
    vector<bool> used(2 * n, false);
    vector<int> left(2 * n), right(2 * n);
    
    for (int i = 0; i < 2 * n; i++) {
        left[i] = i - 1;
        right[i] = i + 1;
        pq.push({b[i], i});
    }
    
    int ans = 0;
    int cnt = 0;
    
    while (cnt < m && !pq.empty()) {
        int val = pq.top().first;
        int idx = pq.top().second;
        pq.pop();
        
        if (used[idx]) continue;
        if (idx >= n) continue; // 只取前n个
        
        ans += val;
        cnt++;
        
        // 反悔：将当前节点与左右邻居合并
        int l = left[idx], r = right[idx];
        if (l >= 0 && r < 2 * n) {
            used[l] = true;
            used[r] = true;
            
            int new_val = b[l] + b[r] - b[idx];
            b[idx] = new_val;
            
            left[idx] = left[l];
            right[idx] = right[r];
            if (left[idx] >= 0) right[left[idx]] = idx;
            if (right[idx] < 2 * n) left[right[idx]] = idx;
            
            pq.push({new_val, idx});
        } else {
            used[idx] = true;
        }
    }
    
    if (cnt < m) {
        cout << "Error!\n";
    } else {
        cout << ans << "\n";
    }
    
    return 0;
}