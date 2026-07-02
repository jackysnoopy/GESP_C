#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    
    int q;
    cin >> q;
    
    while (q--) {
        int s, t;
        cin >> s >> t;
        s--; t--;
        
        // 从(s, h[s])到(t, h[t])
        // 移动：列±1，行±1或不变
        // 行-1: 1体力，行不变: 2体力，行+1: 4体力
        // 约束：行数 >= h[列]
        
        // 贪心：尽量走水平（2体力），必要时爬升（4体力），尽量下坡（1体力）
        
        long long ans = 0;
        
        if (s == t) {
            cout << 0 << "\n";
            continue;
        }
        
        if (s < t) {
            // 向右走
            long long curH = h[s];
            for (int i = s; i < t; i++) {
                long long nextH = h[i + 1];
                if (curH >= nextH) {
                    // 可以下坡或水平
                    ans += 2 + (curH - nextH); // 水平+下坡
                    curH = nextH;
                } else {
                    // 需要爬升
                    ans += 2 + 4 * (nextH - curH); // 水平+爬升
                    curH = nextH;
                }
            }
        } else {
            // 向左走
            long long curH = h[s];
            for (int i = s; i > t; i--) {
                long long nextH = h[i - 1];
                if (curH >= nextH) {
                    ans += 2 + (curH - nextH);
                    curH = nextH;
                } else {
                    ans += 2 + 4 * (nextH - curH);
                    curH = nextH;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
