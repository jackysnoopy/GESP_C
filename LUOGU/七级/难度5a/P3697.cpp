#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll N, M, K, A, B, C, T;
    scanf("%lld%lld%lld", &N, &M, &K);
    scanf("%lld%lld%lld", &A, &B, &C);
    scanf("%lld", &T);
    
    vector<ll> S(M);
    for (int i = 0; i < M; i++) {
        scanf("%lld", &S[i]);
    }
    
    // 计算每种列车的时间
    ll slow_time = A;
    ll express_time = B;
    ll fast_time = C;
    
    // 计算能到达的站数
    ll ans = 0;
    
    // 使用DP或贪心
    // 由于数据范围较大，需要优化
    
    // 简化计算：对于每个站，计算从1号站到该站的最短时间
    for (ll i = 1; i <= N; i++) {
        ll min_time = LLONG_MAX;
        
        // 尝试所有可能的到达方式
        // 1. 直接坐慢车
        min_time = min(min_time, (i - 1) * A);
        
        // 2. 坐快车到某个站，再转慢车
        for (int j = 0; j < M; j++) {
            if (S[j] <= i) {
                ll time = (S[j] - 1) * fast_time + (i - S[j]) * A;
                min_time = min(min_time, time);
            }
        }
        
        // 3. 坐特急到某个站，再转慢车
        for (int j = 0; j < M; j++) {
            if (S[j] <= i) {
                ll time = (S[j] - 1) * express_time + (i - S[j]) * A;
                min_time = min(min_time, time);
            }
        }
        
        if (min_time <= T) {
            ans++;
        }
    }
    
    printf("%lld\n", ans);
    
    return 0;
}
