#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

const int MAXN = 1e5 + 10;

int n, q;
long long p[MAXN], t[MAXN];
int x[MAXN];
long long y[MAXN];

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> p[i] >> t[i] >> x[i];
    }
    for (int i = 1; i <= q; i++) {
        cin >> y[i];
    }
    
    // 对于每个询问，计算最小时间
    // 这里需要更高效的算法，目前是暴力解法
    cout << fixed << setprecision(10);
    for (int i = 1; i <= q; i++) {
        long long dest = y[i];
        double minTime = dest; // 不加油的情况
        
        // 尝试所有可能的加油站组合（暴力，实际上需要优化）
        for (int mask = 0; mask < (1 << n); mask++) {
            double currentTime = 0;
            double speed = 1.0;
            long long lastPos = 0;
            bool valid = true;
            
            for (int j = 1; j <= n; j++) {
                if (p[j] > dest) break;
                
                // 行驶到加油站j
                currentTime += (p[j] - lastPos) / speed;
                lastPos = p[j];
                
                // 如果选择在这个加油站加油
                if (mask & (1 << (j - 1))) {
                    currentTime += t[j];
                    speed *= x[j];
                }
            }
            
            // 行驶到终点
            currentTime += (dest - lastPos) / speed;
            
            if (currentTime < minTime) {
                minTime = currentTime;
            }
        }
        
        cout << minTime << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}