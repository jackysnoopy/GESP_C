#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n;
        scanf("%d", &n);
        
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        
        // 简化处理：将最小的放入T，其余放入S
        long long min_val = *min_element(a.begin(), a.end());
        
        // 计算GCD和LCM（简化）
        long long gcd_val = a[0];
        for (int i = 1; i < n; i++) {
            gcd_val = __gcd(gcd_val, a[i]);
        }
        
        long long lcm_val = a[n-1];
        for (int i = n-2; i >= 0; i--) {
            lcm_val = lcm_val / __gcd(lcm_val, a[i]) * a[i];
        }
        
        printf("%lld\n", abs(gcd_val - lcm_val));
    }
    
    return 0;
}