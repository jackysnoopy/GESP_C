#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
int N, Q;
long long A[MAXN];
int L[MAXN], R[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &A[i]);
    }
    
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }
    
    // 对每个询问暴力枚举
    for (int i = 1; i <= Q; i++) {
        long long ans = 0;
        
        // 枚举中间点b
        for (int b = L[i] + 1; b < R[i]; b++) {
            // 枚举a和c，满足b-a <= c-b
            for (int a = L[i]; a < b; a++) {
                int d1 = b - a;
                int max_c = min(R[i], b + d1);
                for (int c = b + 1; c <= max_c; c++) {
                    ans = max(ans, A[a] + A[b] + A[c]);
                }
            }
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}