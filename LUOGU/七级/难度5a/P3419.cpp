#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
int n, k, p;
int a[MAXN];
int next_use[MAXN];
bool in_memory[MAXN];

int main() {
    scanf("%d%d%d", &n, &k, &p);
    
    for (int i = 1; i <= p; i++) {
        scanf("%d", &a[i]);
    }
    
    // 计算每个位置下一次使用的位置
    vector<int> last_pos(n + 1, p + 1);
    for (int i = p; i >= 1; i--) {
        next_use[i] = last_pos[a[i]];
        last_pos[a[i]] = i;
    }
    
    // 使用优先队列模拟LRU
    priority_queue<pair<int, int>> pq; // (next_use, toy_id)
    int ans = 0;
    
    for (int i = 1; i <= p; i++) {
        int toy = a[i];
        
        if (!in_memory[toy]) {
            ans++;
            
            if ((int)pq.size() == k) {
                int old_toy = pq.top().second;
                pq.pop();
                in_memory[old_toy] = false;
            }
            
            in_memory[toy] = true;
            pq.push({next_use[i], toy});
        } else {
            // 更新优先级
            pq.push({next_use[i], toy});
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}
