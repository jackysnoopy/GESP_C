#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k, x;
    cin >> n >> m >> k >> x;
    
    vector<long long> h(n), g(n);
    for (int i = 0; i < n; i++) cin >> h[i] >> g[i];
    
    // 二分答案：M天后最高灌木高度的最小值
    auto check = [&](long long limit) -> bool {
        // 每天剪枝k次，每次减x
        // M天共可剪M*k次
        long long totalCuts = (long long)m * k;
        
        // 对于每丛灌木，计算需要剪多少次
        long long need = 0;
        for (int i = 0; i < n; i++) {
            long long finalH = h[i] + (long long)m * g[i];
            if (finalH > limit) {
                long long excess = finalH - limit;
                need += (excess + x - 1) / x;
            }
        }
        
        return need <= totalCuts;
    };
    
    long long lo = 0, hi = 2e18;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    
    cout << lo << "\n";
    return 0;
}
