#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

bool canExplode(vector<int>& pos, double R) {
    int n = pos.size();
    
    // Try to find a starting position that can detonate all bales
    for (int start = 0; start < n; start++) {
        double power = R;
        int left = start, right = start;
        
        while (left >= 0 && right < n) {
            // Explode bales within current power range
            while (left >= 0 && pos[start] - pos[left] <= power) {
                left--;
            }
            while (right < n && pos[right] - pos[start] <= power) {
                right++;
            }
            
            // Update power for next level
            power--;
            
            // Check if we can reach further
            if (left < 0 && right >= n) {
                return true;
            }
        }
    }
    
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }
    
    sort(pos.begin(), pos.end());
    
    // Binary search on R
    double low = 0, high = 1e9;
    double answer = high;
    
    for (int iter = 0; iter < 100; iter++) {
        double mid = (low + high) / 2;
        
        if (canExplode(pos, mid)) {
            answer = mid;
            high = mid;
        } else {
            low = mid;
        }
    }
    
    cout << fixed << setprecision(1) << answer << "\n";
    return 0;
}
