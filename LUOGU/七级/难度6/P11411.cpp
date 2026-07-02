#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2005;
int n, k;
int a[MAXN];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 简化处理：计算最长递增子序列长度
    vector<int> lis;
    for (int i = 1; i <= n; i++) {
        auto it = lower_bound(lis.begin(), lis.end(), a[i]);
        if (it == lis.end()) {
            lis.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    
    int lis_len = lis.size();
    
    // 如果最长递增子序列长度 <= k，不需要删除
    if (lis_len <= k) {
        printf("0\n");
    } else {
        // 需要删除 lis_len - k 张牌
        printf("%d\n", lis_len - k);
    }
    
    return 0;
}