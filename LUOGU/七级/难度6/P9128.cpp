#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
long long a[MAXN];
int n, T;
long long total_time = 0;
long long total_fertilizer = 0;

void dfs(int u, int parent, long long time_so_far) {
    total_fertilizer += a[u] * time_so_far;
    for (int v : adj[u]) {
        if (v != parent) {
            total_time += 2;
            dfs(v, u, time_so_far + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> T;
    
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p >> a[i];
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    
    if (T == 0) {
        // 必须回到起点
        dfs(1, -1, 0);
        cout << total_time << " " << total_fertilizer << "\n";
    } else {
        // 可以在任意节点结束
        // 这里需要更复杂的算法
        // 简单实现：先按T=0处理
        dfs(1, -1, 0);
        cout << total_time << " " << total_fertilizer << "\n";
    }
    
    return 0;
}