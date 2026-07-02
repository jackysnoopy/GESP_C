#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Bomb {
    int p, l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Bomb> bombs(n);
    for (int i = 0; i < n; i++) {
        cin >> bombs[i].p >> bombs[i].l >> bombs[i].r;
    }
    
    // Sort by position
    sort(bombs.begin(), bombs.end(), [](const Bomb& a, const Bomb& b) {
        return a.p < b.p;
    });
    
    // For each bomb, its explosion range is [p-l, p+r]
    // When a bomb explodes, it triggers all bombs in its range
    // We want to find the minimum number of bombs to manually trigger
    
    // This is a greedy problem:
    // Sort bombs by position
    // For each bomb that hasn't been triggered, manually trigger it
    // Then mark all bombs in its range as triggered
    
    vector<bool> triggered(n, false);
    int ans = 0;
    
    for (int i = 0; i < n; i++) {
        if (triggered[i]) continue;
        
        // Manually trigger bomb i
        ans++;
        
        // Mark all bombs in its range as triggered
        int left = bombs[i].p - bombs[i].l;
        int right = bombs[i].p + bombs[i].r;
        
        for (int j = i; j < n; j++) {
            if (bombs[j].p >= left && bombs[j].p <= right) {
                triggered[j] = true;
                // Extend range if this bomb triggers others
                left = min(left, bombs[j].p - bombs[j].l);
                right = max(right, bombs[j].p + bombs[j].r);
            } else {
                break;
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
