#include <bits/stdc++.h>
using namespace std;

int main() {
    int M, N, T;
    scanf("%d%d%d", &M, &N, &T);
    
    while (T--) {
        int X, Y;
        scanf("%d%d", &X, &Y);
        
        // 使用Sprague-Grundy定理
        // 对于这种游戏，Grundy值等于X xor Y
        if ((X ^ Y) == 0) {
            printf("Bessie\n");
        } else {
            printf("Farmer John\n");
        }
    }
    
    return 0;
}
