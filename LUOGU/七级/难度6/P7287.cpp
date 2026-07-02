#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long a, b, s;
    cin >> n >> a >> b >> s;
    
    vector<long long> arr(n);
    long long totalPos = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] > 0) totalPos += arr[i];
    }
    
    // 如果已经满足，答案为0
    if (totalPos >= s) {
        cout << 0 << endl;
        return 0;
    }
    
    // 二分答案：使用k次乘法
    // 每次乘法代价b，每次加法代价a
    // 目标：使最大子段和 >= s
    
    // 对于给定的k次乘法，最少需要多少次加法？
    // 贪心：选择最大的正数子段，对它做k次乘法
    // 乘法前需要确保子段和为正
    // 加法可以先增加子段和
    
    // 枚举k次乘法（0到30左右）
    long long ans = LLONG_MAX;
    
    for (int k = 0; k <= 31; k++) {
        // k次乘法的代价
        long long mulCost = (long long)k * b;
        if (mulCost >= ans) break;
        
        // 对于给定的k，最少需要多少次加法？
        // 每次加法增加子段和1，乘法后变成2^k倍
        // 需要：(initial + add) * 2^k >= s
        // add >= ceil(s / 2^k) - initial
        
        // 选择最大的初始子段和
        long long maxSub = 0, cur = 0;
        for (int i = 0; i < n; i++) {
            cur = max(cur + arr[i], 0LL);
            maxSub = max(maxSub, cur);
        }
        
        long long needed = (s + (1LL << k) - 1) / (1LL << k);
        long long addNeed = max(0LL, needed - maxSub);
        long long addCost = addNeed * a;
        
        ans = min(ans, mulCost + addCost);
    }
    
    cout << ans << endl;
    return 0;
}
