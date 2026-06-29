#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    
    // 使用数学公式
    // 最终结果是 sum(a[i] * C(n-1, i-1)) for i=1 to n
    // 为了最大化，应该把大数放在系数大的位置
    
    vector<int> coeff(n);
    for (int i = 0; i < n; i++) {
        coeff[i] = 1;
        for (int j = 0; j < i; j++) {
            coeff[i] = coeff[i] * (n - 1 - j) / (j + 1);
            coeff[i] %= MOD;
        }
    }
    
    // 排序系数
    sort(coeff.begin(), coeff.end(), greater<int>());
    
    // 将1到n分配给系数
    long long ans = 0;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) nums[i] = i + 1;
    sort(nums.begin(), nums.end(), greater<int>());
    
    for (int i = 0; i < n; i++) {
        ans = (ans + (long long)coeff[i] * nums[i]) % MOD;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}
