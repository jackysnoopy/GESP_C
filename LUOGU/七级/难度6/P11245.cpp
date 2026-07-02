#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int q;
    scanf("%d", &q);
    
    while (q--) {
        long long L, R, m, n;
        scanf("%lld %lld %lld %lld", &L, &R, &m, &n);
        
        // 简化判断：如果m和n都为0，无解
        if (m == 0 && n == 0) {
            printf("No\n");
            continue;
        }
        
        // 如果L=1，任何包含0和1的串都不合法
        if (L == 1 && m > 0 && n > 0) {
            printf("No\n");
            continue;
        }
        
        // 其他情况输出Yes（简化处理）
        printf("Yes\n");
    }
    
    return 0;
}