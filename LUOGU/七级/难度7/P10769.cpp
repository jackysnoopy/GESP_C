#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<ll> s(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> s[i];
    
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    
    int p;
    cin >> p;
    
    while (p--) {
        vector<ll> t(n);
        for (int i = 0; i < n; i++) cin >> t[i];
        
        int qi;
        cin >> qi;
        
        vector<ll> k(qi);
        for (int i = 0; i < qi; i++) cin >> k[i];
        
        // 公交接驳问题
        // 对于每个k，计算最小不满意度
        for (int qi_idx = 0; qi_idx < qi; qi_idx++) {
            ll ki = k[qi_idx];
            
            // 简单情况：k足够大时，可以在每个站点发车
            if (ki >= n) {
                cout << "0";
                if (qi_idx < qi - 1) cout << " ";
                continue;
            }
            
            // 计算每个站点的等待时间
            ll total_unsat = 0;
            vector<ll> bus_time(n, 0);
            
            // 模拟k班公交车
            for (int bus = 0; bus < ki; bus++) {
                // 每班车从某个站点出发
                int start = bus % n;
                ll departure = t[start];
                
                // 计算到达每个站点的时间
                ll current_time = departure;
                for (int station = start; station < n; station++) {
                    if (station > start) {
                        current_time += s[station - 1];
                    }
                    bus_time[station] = max(bus_time[station], current_time);
                }
            }
            
            // 计算不满意度
            for (int i = 0; i < n; i++) {
                ll wait = max(0LL, bus_time[i] - t[i]);
                total_unsat += wait * v[i];
            }
            
            cout << total_unsat;
            if (qi_idx < qi - 1) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
