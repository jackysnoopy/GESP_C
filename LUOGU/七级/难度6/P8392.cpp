#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    long long l;
    cin >> m >> l;
    
    vector<long long> a(2 * m + 1);
    for (int i = 0; i <= 2 * m; i++) {
        cin >> a[i];
    }
    
    // Simplified approach
    long long total = 0;
    long long weight = 0;
    
    for (int i = 0; i <= 2 * m; i++) {
        long long w = i - m;
        if (w >= 0) {
            total += a[i] * w;
            weight += a[i];
        } else {
            total += a[i] * w;
            weight += a[i];
        }
    }
    
    if (total < l) {
        cout << "impossible" << endl;
    } else {
        // Simple greedy
        long long ans = 0;
        long long current = 0;
        
        for (int i = 2 * m; i >= 0; i--) {
            long long w = i - m;
            long long take = min(a[i], (l - current + w - 1) / w);
            if (w > 0 && take > 0) {
                ans += take;
                current += take * w;
            }
        }
        
        cout << ans << endl;
    }
    
    return 0;
}