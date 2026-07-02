#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 判断是否为质数
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int h;
        cin >> h;
        
        int ans = -1;
        
        // 枚举物理攻击次数 k
        for (int k = 1; k <= 60; k++) {
            long long physicalDamage = (1LL << k) - 1; // 2^k - 1
            
            if (physicalDamage > h) break;
            
            // 不使用魔法攻击的情况
            if (physicalDamage == h) {
                ans = k;
                break;
            }
            
            // 使用魔法攻击的情况
            int magicDamage = h - physicalDamage;
            if (magicDamage > 0 && isPrime(magicDamage)) {
                if (ans == -1 || k + 1 < ans) {
                    ans = k + 1; // k次物理 + 1次魔法
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
