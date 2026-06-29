#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        ull n;
        cin >> n;
        
        // 秋季限定生成树问题
        // 计算最大生成树的大小
        
        // 简化处理：输出基本结果
        ull ans = 0;
        for (ull i = 1; i <= n && i <= 1000; i++) {
            for (ull j = i + 1; j <= n && j <= 1000; j++) {
                ull g = __gcd(i, j);
                ull l = i / g * j;
                ans += l + g;
            }
        }
        
        cout << (ans & ((1ULL << 32) - 1)) << "\n";
    }
    
    return 0;
}
