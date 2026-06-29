#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    
    // 采蘑菇问题
    // 每天早上选择一块地采蘑菇，晚上长出a[i]个蘑菇
    
    // 对于k=1,2,...,n，求最多能采多少蘑菇
    for (int k = 1; k <= n; k++) {
        ll total = 0;
        
        // 贪心：每天选择当前蘑菇最多的地采
        // 使用优先队列维护
        vector<ll> mushrooms(n);
        for (int i = 0; i < n; i++) {
            mushrooms[i] = b[i];
        }
        
        for (int day = 0; day < k; day++) {
            // 找到蘑菇最多的地
            int best = 0;
            for (int i = 1; i < n; i++) {
                if (mushrooms[i] > mushrooms[best]) {
                    best = i;
                }
            }
            
            // 采蘑菇
            total += mushrooms[best];
            
            // 晚上长出新蘑菇
            mushrooms[best] += a[best];
        }
        
        cout << total << "\n";
    }
    
    return 0;
}
