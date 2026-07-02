#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string m;
    cin >> m;
    
    int n = m.length();
    
    // Find the mask pattern
    // The mask is the intersection of all valid solutions
    // We need to find a profile p' that produces this mask
    
    // First, find the forced positions (marked with #)
    vector<int> forced;
    for (int i = 0; i < n; i++) {
        if (m[i] == '#') {
            forced.push_back(i);
        }
    }
    
    if (forced.empty()) {
        // No forced positions, output empty profile
        cout << 0 << endl;
        return 0;
    }
    
    // Group forced positions into consecutive segments
    vector<pair<int, int>> segments;
    int start = forced[0];
    for (int i = 1; i < forced.size(); i++) {
        if (forced[i] != forced[i-1] + 1) {
            segments.push_back({start, forced[i-1]});
            start = forced[i];
        }
    }
    segments.push_back({start, forced.back()});
    
    // Check if the mask is valid
    // Between consecutive segments, there must be at least one empty cell
    for (int i = 1; i < segments.size(); i++) {
        if (segments[i].first <= segments[i-1].second + 1) {
            // Segments are too close
            cout << -1 << endl;
            return 0;
        }
    }
    
    // The profile is the lengths of the forced segments
    cout << segments.size() << endl;
    for (int i = 0; i < segments.size(); i++) {
        if (i > 0) cout << " ";
        cout << segments[i].second - segments[i].first + 1;
    }
    cout << endl;
    
    return 0;
}
