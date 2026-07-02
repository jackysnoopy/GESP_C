#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, D;
    cin >> N >> D;
    
    int A, B;
    cin >> A >> B;
    
    vector<long long> m(N);
    for (int i = 0; i < N; i++) {
        cin >> m[i];
    }
    
    // 简化的贪心策略
    // 每天增加 A 瓶，偷走 B 瓶
    // 净增 A-B 瓶每天
    // 为了让 sum(M^2) 最大，应该让牛奶分布尽可能均匀
    
    // 计算每个瓶子的最终牛奶量
    // John 选择 A 个瓶子加 1，Nhoj 选择 B 个非空瓶子减 1
    // 这是一个博弈问题
    
    // 简化处理：假设最优策略下，每个瓶子的最终牛奶量
    long long total_added = (long long)D * A;
    long long total_stolen = (long long)D * B;
    
    // 平均分配
    long long base = total_added / N;
    long long extra = total_added % N;
    
    long long ans = 0;
    for (int i = 0; i < N; i++) {
        long long val = m[i] + base;
        if (i < extra) val++;
        // 减去被偷走的（均匀分布）
        val -= total_stolen / N;
        if (val < 0) val = 0;
        ans = (ans + val % MOD * (val % MOD)) % MOD;
    }
    
    cout << ans << endl;
    
    return 0;
}
