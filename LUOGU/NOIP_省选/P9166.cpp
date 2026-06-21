#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, x;
    cin >> n >> m >> x;
    vector<pair<int,int>> tracks(m);
    for (int i = 0; i < m; i++) cin >> tracks[i].first >> tracks[i].second;
    
    sort(tracks.begin(), tracks.end());
    
    // Merge overlapping intervals
    vector<pair<int,int>> merged;
    for (auto& t : tracks) {
        if (!merged.empty() && merged.back().second >= t.first) {
            merged.back().second = max(merged.back().second, t.second);
        } else {
            merged.push_back(t);
        }
    }
    
    // Find component containing x
    int compL = -1, compR = -1;
    for (auto& mg : merged) {
        if (mg.first <= x && mg.second >= x) {
            compL = mg.first;
            compR = mg.second;
            break;
        }
    }
    
    // Going left from x: can reach any station in [compL, x]
    // The endpoints reachable going left: left endpoints l_i where l_i is in [compL, x]
    // (l_i < x, since train must move at least one station)
    // Going right from x: can reach any station in [x, compR]
    // The endpoints reachable going right: right endpoints r_i where r_i is in [x, compR]
    // (r_i > x)
    
    set<int> result;
    for (auto& t : tracks) {
        if (t.first >= compL && t.second <= compR) {
            if (t.first < x) result.insert(t.first);
            if (t.second > x) result.insert(t.second);
        }
    }
    
    bool first = true;
    for (int v : result) {
        if (!first) cout << " ";
        cout << v;
        first = false;
    }
    cout << "\n";
    return 0;
}
