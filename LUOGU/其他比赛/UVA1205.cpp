#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Node {
    int cost, cnt, parent;
    double avg;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n, root;
        cin >> n >> root;
        if (n == 0 && root == 0) break;
        
        vector<Node> nodes(n + 1);
        long long total = 0;
        for (int i = 1; i <= n; i++) {
            cin >> nodes[i].cost;
            nodes[i].cnt = 1;
            nodes[i].avg = nodes[i].cost;
            total += nodes[i].cost;
        }
        
        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            nodes[b].parent = a;
        }
        
        for (int iter = 1; iter < n; iter++) {
            // 找平均代价最大的非根节点
            int best = -1;
            double best_avg = -1;
            for (int i = 1; i <= n; i++) {
                if (i != root && nodes[i].parent != 0 && nodes[i].avg > best_avg) {
                    best_avg = nodes[i].avg;
                    best = i;
                }
            }
            
            if (best == -1) break;
            
            int p = nodes[best].parent;
            total += nodes[best].cost * nodes[p].cnt;
            nodes[p].cnt += nodes[best].cnt;
            nodes[p].cost += nodes[best].cost;
            nodes[p].avg = (double)nodes[p].cost / nodes[p].cnt;
            
            // 将 best 的子节点挂在 p 下
            for (int i = 1; i <= n; i++)
                if (nodes[i].parent == best)
                    nodes[i].parent = p;
            
            nodes[best].parent = 0; // 标记已合并
        }
        
        cout << total << "\n";
    }
    
    return 0;
}