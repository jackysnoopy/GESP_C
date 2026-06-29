#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, g, b, d;
    cin >> n >> g >> b >> d;
    
    vector<pair<int, int>> stations(n);
    for (int i = 0; i < n; i++) {
        cin >> stations[i].first >> stations[i].second;
    }
    
    sort(stations.begin(), stations.end());
    stations.push_back({d, 0});
    
    long long ans = 0;
    int cur_fuel = b;
    int last_pos = 0;
    
    for (int i = 0; i < n; i++) {
        int dist = stations[i].first - last_pos;
        if (cur_fuel < dist) {
            cout << -1 << "\n";
            return 0;
        }
        cur_fuel -= dist;
        
        int next_cheaper = -1;
        for (int j = i + 1; j <= n; j++) {
            if (stations[j].second < stations[i].second) {
                next_cheaper = j;
                break;
            }
        }
        
        if (next_cheaper == -1) {
            int need = g - cur_fuel;
            ans += (long long)need * stations[i].second;
            cur_fuel = g;
        } else {
            int need_to_reach = stations[next_cheaper].first - stations[i].first;
            int need = max(0, need_to_reach - cur_fuel);
            need = min(need, g - cur_fuel);
            if (need > 0) {
                ans += (long long)need * stations[i].second;
                cur_fuel += need;
            }
        }
        
        last_pos = stations[i].first;
    }
    
    cout << ans << "\n";
    return 0;
}
