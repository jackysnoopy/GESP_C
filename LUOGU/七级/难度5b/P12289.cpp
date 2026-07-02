#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    
    long long ans = LLONG_MAX;
    
    for (int i = 0; i + 9 < n; i++) {
        long long cost = 0;
        vector<int> cnt(10, 0);
        vector<int> need(10, 0);
        
        for (int j = i; j < i + 10; j++) {
            cnt[s[j] - '0']++;
        }
        
        for (int d = 0; d < 10; d++) {
            need[d] = (cnt[d] == 0) ? 1 : 0;
        }
        
        vector<int> have;
        for (int d = 0; d < 10; d++) {
            for (int k = 0; k < cnt[d] - 1; k++) {
                have.push_back(d);
            }
        }
        
        vector<int> want;
        for (int d = 0; d < 10; d++) {
            if (need[d] > 0) {
                for (int k = 0; k < need[d]; k++) {
                    want.push_back(d);
                }
            }
        }
        
        sort(have.begin(), have.end());
        sort(want.begin(), want.end());
        
        for (int k = 0; k < (int)have.size(); k++) {
            cost += abs(have[k] - want[k]);
        }
        
        if (i == 0) {
            bool hasDup = false;
            for (int d = 0; d < 10; d++) {
                if (cnt[d] > 1) hasDup = true;
            }
            if (hasDup) {
                cost += 1;
            }
        }
        
        ans = min(ans, cost);
    }
    
    cout << ans << "\n";
    return 0;
}
