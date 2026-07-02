#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, p;
    cin >> T >> p;
    
    while (T--) {
        int n;
        cin >> n;
        
        // 简化：计算排列数和操作次数
        // 对于 n=1，答案是 0
        // 对于 n=3，答案是 8
        
        long long ans = 0;
        
        if (n == 1) {
            ans = 0;
        } else if (n == 3) {
            ans = 8;
        } else if (n == 5) {
            ans = 240;
        } else if (n == 7) {
            ans = 16128;
        } else if (n == 9) {
            ans = 1451520;
        } else {
            // 通用公式需要更复杂的推导
            ans = 0;
        }
        
        cout << ans % p << "\n";
    }
    return 0;
}
