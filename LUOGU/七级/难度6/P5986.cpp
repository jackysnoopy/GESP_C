#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    multiset<long long> fish;
    for (int i = 0; i < n; i++) {
        long long w;
        cin >> w;
        fish.insert(w);
    }
    
    int q;
    cin >> q;
    
    while (q--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            long long s, k;
            cin >> s >> k;
            
            if (s >= k) {
                cout << 0 << "\n";
                continue;
            }
            
            int cnt = 0;
            long long cur = s;
            bool ok = false;
            
            while (cur < k) {
                auto it = fish.upper_bound(cur);
                if (it == fish.end()) {
                    break;
                }
                cur += *it;
                fish.erase(it);
                cnt++;
                if (cur >= k) {
                    ok = true;
                    break;
                }
            }
            
            if (ok) {
                cout << cnt << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else if (op == 2) {
            long long w;
            cin >> w;
            fish.insert(w);
        } else {
            long long w;
            cin >> w;
            auto it = fish.find(w);
            if (it != fish.end()) {
                fish.erase(it);
            }
        }
    }
    
    return 0;
}
