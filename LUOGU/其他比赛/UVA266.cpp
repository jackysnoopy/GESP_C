#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<int> stamps(n);
        for (int i = 0; i < n; i++) {
            cin >> stamps[i];
        }
        sort(stamps.begin(), stamps.end());
        
        int target;
        while (cin >> target && target != 0) {
            int dp[10001];
            fill(dp, dp + 10001, 10000);
            dp[0] = 0;
            
            for (int v = 1; v <= target; v++) {
                for (int s : stamps) {
                    if (s > v) break;
                    if (dp[v - s] + 1 < dp[v]) {
                        dp[v] = dp[v - s] + 1;
                    }
                }
            }
            
            if (dp[target] < 10000) {
                cout << dp[target] << endl;
            } else {
                cout << "无法组成目标面值" << endl;
            }
        }
    }
    return 0;
}
