#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k, x;
    cin >> n >> m >> k >> x;
    
    vector<int> height(n), dailyGrowth(n);
    for (int i = 0; i < n; i++) {
        cin >> height[i] >> dailyGrowth[i];
    }
    
    for (int day = 0; day < m; day++) {
        for (int i = 0; i < n; i++) {
            height[i] += dailyGrowth[i];
        }
        for (int i = 0; i < k; i++) {
            int maxHeight = 0, maxIdx = 0;
            for (int j = 0; j < n; j++) {
                if (height[j] > maxHeight) {
                    maxHeight = height[j];
                    maxIdx = j;
                }
            }
            if (height[maxIdx] >= x) {
                height[maxIdx] -= x;
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, height[i]);
    }
    
    cout << ans << endl;
    return 0;
}