#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].first >> cows[i].second;
    }
    
    // Sort by start position
    sort(cows.begin(), cows.end());
    
    long long total = m;
    int cur_pos = 0;
    
    for (int i = 0; i < n; i++) {
        int start = cows[i].first;
        int end = cows[i].second;
        
        if (start >= cur_pos) {
            // Move to start, then to end
            total += (start - cur_pos);
            total += abs(end - start);
            cur_pos = end;
        } else {
            // Move to start, then to end
            total += (start - cur_pos);
            total += abs(end - start);
            cur_pos = end;
        }
    }
    
    cout << total << "\n";
    return 0;
}
