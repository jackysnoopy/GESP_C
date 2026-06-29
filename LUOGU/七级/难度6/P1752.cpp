#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, p, q;
    cin >> n >> m >> p >> q;
    
    vector<pair<int, int>> dishes(m);
    for (int i = 0; i < m; i++) {
        cin >> dishes[i].first >> dishes[i].second;
    }
    
    vector<int> picky(p);
    for (int i = 0; i < p; i++) {
        cin >> picky[i];
    }
    
    vector<int> poor(q);
    for (int i = 0; i < q; i++) {
        cin >> poor[i];
    }
    
    // Sort dishes by deliciousness
    sort(dishes.begin(), dishes.end());
    
    // Sort picky people by minimum deliciousness (ascending)
    sort(picky.begin(), picky.end());
    
    // Sort poor people by maximum price (ascending)
    sort(poor.begin(), poor.end());
    
    // Binary search on number of weeks
    int low = 1, high = m;
    int answer = -1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        // Check if mid weeks are enough
        // Each person can order at most mid dishes
        vector<bool> used(m, false);
        int ordered = 0;
        
        // Assign dishes to picky people (sorted by threshold ascending)
        for (int i = 0; i < p; i++) {
            int min_delicious = picky[i];
            int count = 0;
            // Find dishes with deliciousness >= min_delicious
            int idx = lower_bound(dishes.begin(), dishes.end(), make_pair(min_delicious, 0)) - dishes.begin();
            while (count < mid && idx < m) {
                if (!used[idx]) {
                    used[idx] = true;
                    ordered++;
                    count++;
                }
                idx++;
            }
        }
        
        // Assign dishes to poor people (sorted by threshold ascending)
        for (int i = 0; i < q; i++) {
            int max_price = poor[i];
            int count = 0;
            // Find dishes with price <= max_price (search from end)
            for (int j = m - 1; j >= 0 && count < mid; j--) {
                if (!used[j] && dishes[j].second <= max_price) {
                    used[j] = true;
                    ordered++;
                    count++;
                }
            }
        }
        
        // Check if all dishes can be ordered
        // Each remaining dish needs at least one person who can order it
        // Since we have n - p - q other people who can order any dish
        int remaining = m - ordered;
        int available_people = n - p - q;
        
        if (remaining <= available_people * mid) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    cout << answer << "\n";
    return 0;
}
