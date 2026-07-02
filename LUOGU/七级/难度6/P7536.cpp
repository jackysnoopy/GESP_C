#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k;
    long long A, B;
    cin >> k >> A >> B;
    
    vector<double> nums(k);
    for (int i = 0; i < k; i++) cin >> nums[i];
    
    // 对于每个数，它是某个x的倍数：nums[i] = c * x
    // 需要找到最少的x使得所有数都能被表示
    // 每个x生成 0, x, 2x, 3x, ... 中在[A,B]内的数
    
    // 贪心：从最大的数开始，找能生成它的最大x
    // 然后移除能被该x生成的所有数
    
    vector<bool> used(k, false);
    vector<double> result;
    
    // 按降序处理
    vector<int> order(k);
    for (int i = 0; i < k; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) {
        return nums[a] > nums[b];
    });
    
    for (int idx : order) {
        if (used[idx]) continue;
        double val = nums[idx];
        
        // 找能生成val的最大x
        // val = c * x, x = val / c
        // x应该使得A <= c*x <= B
        // 最大的x = val (当c=1时)
        
        // 但x需要使得所有未使用的数中，能被x生成的都移除
        // 贪心：x = val (最小的倍数)
        double x = val;
        result.push_back(x);
        
        // 移除能被x生成的数
        for (int i = 0; i < k; i++) {
            if (used[i]) continue;
            double v = nums[i];
            // 检查v是否是x的倍数
            double ratio = v / x;
            long long r = (long long)(ratio + 0.5);
            if (r > 0 && fabs(ratio - r) < 1e-6) {
                // v = r * x
                // 检查A <= c*x <= B对于所有c=0..r
                // 实际上只要检查r*x在[A,B]内即可
                if (r * x >= A - 1e-9 && r * x <= B + 1e-9) {
                    used[i] = true;
                }
            }
        }
    }
    
    cout << result.size() << "\n";
    for (double x : result) {
        cout << x << "\n";
    }
    
    return 0;
}
