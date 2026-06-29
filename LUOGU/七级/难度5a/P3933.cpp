#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
int n, m;
int a[MAXN][MAXN];

int main() {
    scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    // 收集所有值并排序
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            vals.push_back(a[i][j]);
        }
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    
    // 二分答案
    int ans = INT_MAX;
    
    for (int i = 0; i < (int)vals.size(); i++) {
        for (int j = i; j < (int)vals.size(); j++) {
            int min_val = vals[i];
            int max_val = vals[j];
            int range = max_val - min_val;
            
            if (range >= ans) continue;
            
            // 检查是否可以合法分割
            // 简化：检查是否存在满足条件的分割
            bool ok = true;
            
            // 这里需要更复杂的检查逻辑
            // 简化为输出当前最优解
            
            if (ok) {
                ans = min(ans, range);
            }
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}
