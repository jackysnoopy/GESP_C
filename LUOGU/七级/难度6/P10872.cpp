#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, K, L;
    scanf("%d %d %d", &N, &K, &L);
    
    // 计算最小重叠数
    int F = 0;
    if (K > 0 && L > 0) {
        // 最小重叠数 = max(0, K + L - N)
        F = max(0, K + L - N);
    }
    
    printf("%d\n", F);
    
    // 构造S
    string S(N, '0');
    for (int i = 0; i < K; i++) {
        S[i] = '1';
    }
    
    // 构造T
    string T(N, '0');
    for (int i = 0; i < L; i++) {
        T[i] = '1';
    }
    
    cout << S << endl;
    cout << T << endl;
    
    return 0;
}