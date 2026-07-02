#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<long long> a(n), h(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> h[i];
    }
    
    vector<long long> x(k);
    for (int i = 0; i < k; i++) {
        cin >> x[i];
    }
    
    vector<pair<long long, long long>> monsters(n);
    for (int i = 0; i < n; i++) {
        monsters[i] = {a[i], h[i]};
    }
    sort(monsters.begin(), monsters.end());
    sort(x.begin(), x.end());
    
    long long total_cost = 0;
    for (int i = 0; i < n; i++) {
        long long monster_pos = monsters[i].first;
        long long health = monsters[i].second;
        
        auto it = lower_bound(x.begin(), x.end(), monster_pos);
        long long min_dist = INF;
        if (it != x.end()) {
            min_dist = min(min_dist, abs(monster_pos - *it));
        }
        if (it != x.begin()) {
            --it;
            min_dist = min(min_dist, abs(monster_pos - *it));
        }
        
        total_cost += min(health, min_dist);
    }
    
    cout << total_cost << endl;
    
    return 0;
}
