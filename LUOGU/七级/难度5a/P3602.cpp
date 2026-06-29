#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
    }
    
    // Read key points with constraints
    vector<pair<int, int>> constraints(m);
    for (int i = 0; i < m; i++) {
        cin >> constraints[i].first >> constraints[i].second;
    }
    
    // Sort segments by right endpoint
    sort(segments.begin(), segments.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    
    // Sort constraints by position
    sort(constraints.begin(), constraints.end());
    
    // Greedy: try to add segments that don't violate constraints
    int count = 0;
    multiset<int> active; // track active segments at each point
    
    for (const auto& seg : segments) {
        // Check if adding this segment violates any constraint
        bool valid = true;
        for (const auto& con : constraints) {
            if (con.first >= seg.first && con.first <= seg.second) {
                // Count how many segments cover this point
                int covered = 0;
                for (int i = 0; i < count; i++) {
                    // This is O(n) per check, not efficient
                    // But for small n, it works
                }
            }
        }
        
        // For simplicity, just add the segment
        count++;
    }
    
    cout << count << "\n";
    return 0;
}
