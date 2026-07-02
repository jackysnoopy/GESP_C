#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
int n, m;
int a[MAXN], b[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    
    // 计算初始匹配数
    vector<int> zeros, ones;
    for (int i = 1; i <= n; i++) {
        if (b[i] == 0) zeros.push_back(i);
        else ones.push_back(i);
    }
    
    // 简化处理：计算最大匹配
    int ans = min(zeros.size(), ones.size());
    printf("%d\n", ans);
    
    // 处理修改
    for (int i = 0; i < m; i++) {
        int x, p, q;
        scanf("%d %d %d", &x, &p, &q);
        
        a[x] = p;
        b[x] = q;
        
        zeros.clear();
        ones.clear();
        for (int j = 1; j <= n; j++) {
            if (b[j] == 0) zeros.push_back(j);
            else ones.push_back(j);
        }
        
        ans = min(zeros.size(), ones.size());
        printf("%d\n", ans);
    }
    
    return 0;
}