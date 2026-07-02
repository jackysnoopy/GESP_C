#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        long long n;
        scanf("%lld", &n);
        
        // 构造字典序最小的有根树，使得所有节点度数异或为0
        // 对于n个节点，度数之和为2*(n-1)
        // 需要所有度数异或为0
        
        if (n == 2) {
            // 节点1是根，节点2的父节点是1
            // 度数：1的度数是1，2的度数是1，异或为0
            printf("2\n");
        } else if (n == 3) {
            // 无解：度数之和为4，但三个数异或为0需要偶数个1
            printf("-1\n");
        } else {
            // 构造：让节点1连接所有其他节点
            // 度数：1的度数是n-1，其他节点度数是1
            // 异或：(n-1) XOR 1 XOR 1 XOR ... XOR 1 (n-2个1)
            // 如果n-1是偶数，异或为0
            // 如果n-1是奇数，需要调整
            
            long long ans = 0;
            if (n % 2 == 0) {
                // n是偶数，n-1是奇数
                // 节点1连接节点2,3,...,n
                // 度数异或：(n-1) XOR 1 XOR 1 XOR ... XOR 1
                // = (n-1) XOR (n-2)
                // 如果n-1是奇数，n-2是偶数，异或为奇数
                // 需要调整：让节点2连接节点3
                // 度数：1的度数是n-2，2的度数是2，3的度数是2，其他是1
                // 异或：(n-2) XOR 2 XOR 2 XOR 1 XOR ... XOR 1
                // = (n-2) XOR (n-3)
                // 如果n-2是偶数，n-3是奇数，异或为奇数
                
                // 简单构造：链状结构
                for (int i = 2; i <= n; i++) {
                    ans = (ans + (long long)i * (i - 1)) % MOD;
                }
            } else {
                // n是奇数，n-1是偶数
                // 节点1连接节点2,3,...,n
                // 度数异或：(n-1) XOR 1 XOR 1 XOR ... XOR 1
                // = (n-1) XOR (n-2)
                // 如果n-1是偶数，n-2是奇数，异或为奇数
                // 需要调整
                
                // 简单构造：链状结构
                for (int i = 2; i <= n; i++) {
                    ans = (ans + (long long)i * (i - 1)) % MOD;
                }
            }
            
            printf("%lld\n", ans);
        }
    }
    
    return 0;
}