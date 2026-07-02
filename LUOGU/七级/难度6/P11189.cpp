#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
int n;
int father[MAXN];
long long a[MAXN];
vector<int> children[MAXN];
long long subtree_sum[MAXN];

void dfs(int u) {
    subtree_sum[u] = a[u];
    for (int v : children[u]) {
        dfs(v);
        subtree_sum[u] += subtree_sum[v];
    }
}

int main() {
    int c, t;
    scanf("%d %d", &c, &t);
    
    while (t--) {
        scanf("%d", &n);
        
        for (int i = 1; i <= n; i++) {
            children[i].clear();
        }
        
        for (int i = 2; i <= n; i++) {
            scanf("%d", &father[i]);
            children[father[i]].push_back(i);
        }
        
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        
        dfs(1);
        
        // 检查是否可行
        bool possible = true;
        for (int i = 1; i <= n; i++) {
            if (subtree_sum[i] < 0) {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            printf("Huoyu\n");
        } else {
            printf("Shuiniao\n");
        }
    }
    
    return 0;
}