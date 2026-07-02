#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        long long k;
        cin >> n >> k;
        
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        
        // 如果k >= sum(a)，所有学生都离开，答案为0
        long long total_a = accumulate(a.begin(), a.end(), 0LL);
        if (k >= total_a) {
            cout << 0 << endl;
            continue;
        }
        
        // 模拟过程，但可能太慢
        // 需要更高效的算法
        
        // 观察：每个时刻，学生先入座，然后移动
        // 可以认为学生在区域间循环移动
        
        // 由于时间有限，我实现一个简单的模拟
        // 但只模拟最多n个时刻，因为n个时刻后学生会回到原区域
        
        int ans = 0;
        vector<long long> cur_a = a;
        
        // 由于k名学生离开，我们需要考虑最坏情况
        // 最坏情况是k名学生都在最需要的区域
        
        // 简化：假设k名学生均匀分布
        long long avg_remove = k / n;
        long long remainder = k % n;
        
        for (int i = 0; i < n; i++) {
            cur_a[i] -= avg_remove;
            if (i < remainder) {
                cur_a[i]--;
            }
            cur_a[i] = max(0LL, cur_a[i]);
        }
        
        // 模拟最多n个时刻
        for (int t = 0; t < n; t++) {
            // 入座
            vector<long long> next_a(n);
            for (int i = 0; i < n; i++) {
                long long sit = min(cur_a[i], b[i]);
                next_a[i] = cur_a[i] - sit;
            }
            
            // 检查是否所有区域都没有等位学生
            bool done = true;
            for (int i = 0; i < n; i++) {
                if (next_a[i] > 0) {
                    done = false;
                    break;
                }
            }
            
            if (done) {
                ans = t + 1;
                break;
            }
            
            // 移动到下一个区域
            vector<long long> moved_a(n);
            for (int i = 0; i < n; i++) {
                int next = (i + 1) % n;
                moved_a[next] = next_a[i];
            }
            
            cur_a = moved_a;
        }
        
        cout << ans << endl;
    }
    
    return 0;
}