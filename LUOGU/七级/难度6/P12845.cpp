#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> p(n), l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> l[i] >> r[i];
    }
    
    // 按位置排序
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return p[a] < p[b];
    });
    
    // 贪心：每次选择能引爆最多炸弹的
    // 使用区间覆盖的思想
    
    int ans = 0;
    vector<bool> exploded(n, false);
    
    for (int i = 0; i < n; i++) {
        if (exploded[idx[i]]) continue;
        
        ans++;
        // BFS/DFS 引爆所有能引爆的
        vector<int> queue = {idx[i]};
        exploded[idx[i]] = true;
        
        int head = 0;
        while (head < queue.size()) {
            int u = queue[head++];
            int left = p[u] - l[u];
            int right = p[u] + r[u];
            
            for (int v = 0; v < n; v++) {
                if (!exploded[idx[v]] && p[idx[v]] >= left && p[idx[v]] <= right) {
                    exploded[idx[v]] = true;
                    queue.push_back(idx[v]);
                }
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
