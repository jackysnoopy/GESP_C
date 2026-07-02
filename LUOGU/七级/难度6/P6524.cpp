#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    
    sort(x.begin(), x.end());
    
    if (k == 1) {
        long long ans = 0;
        for (int i = 0; i < m / 2; i++) {
            ans += x[n - 1 - i] - x[i];
        }
        cout << ans << "\n";
    } else {
        long long max1 = 0;
        for (int i = 0; i < m / 2; i++) {
            max1 += x[n - 1 - i] - x[i];
        }
        
        long long max2 = 0;
        bool found = false;
        
        for (int i = 0; i < m / 2; i++) {
            long long cur = 0;
            for (int j = 0; j < m / 2; j++) {
                if (j == i) cur += x[n - 1 - j] - x[j + 1];
                else cur += x[n - 1 - j] - x[j];
            }
            if (cur < max1) {
                max2 = max(max2, cur);
                found = true;
            }
        }
        
        if (found) cout << max2 << "\n";
        else cout << "-1\n";
    }
    
    return 0;
}
