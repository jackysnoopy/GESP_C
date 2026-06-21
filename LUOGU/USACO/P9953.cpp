#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n), s(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> s[i];
    // Sort by position
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) { return x[a] < x[b]; });
    // Find R: max distance between consecutive sick cows that are connected
    // Two sick cows at distance d: if d <= 2R, they could be connected
    // A healthy cow at distance d from sick: if d <= R, it should be sick (contradiction)
    // So R < min distance between sick and healthy neighbors
    // And R >= (max gap between consecutive sick cows) / 2... no
    // 
    // R is bounded by: for each pair of adjacent cows (by position):
    // If both sick: R >= distance/2 (to be connected)
    // If one sick, one healthy: R < distance (to not infect)
    // 
    // Actually: R must satisfy:
    // - For any sick cow adjacent to healthy cow: distance > R
    // - For any two sick cows: if they should be connected, distance <= 2R
    // 
    // The minimum initial infected = minimum connected components of sick cows
    // where edges exist if distance <= 2R
    // 
    // R is determined by: R < min distance from any sick to adjacent healthy
    // And R >= ceil(max gap between connected sick / 2)? 
    // Actually R can be anything. The problem says "存在一个半径R" - there EXISTS an R.
    // We need to find R that minimizes initial infected count.
    // 
    // Key: find R that minimizes # connected components of sick cows
    // (with edges if distance <= 2R), subject to:
    // For every sick-healthy adjacent pair, distance > R.
    // 
    // So R < min(sick-healthy distance) for all adjacent sick-healthy pairs.
    // And we want to maximize 2R to connect more sick cows.
    // 
    // Let minSH = min distance between adjacent sick and healthy cows.
    // R can be at most minSH - 1 (integer distances? positions are integers).
    // Actually R doesn't need to be integer. R < minSH.
    // 
    // Sort positions. Find all gaps between consecutive cows.
    // For each gap between sick cow i and healthy cow j (or vice versa): R < gap.
    // For each gap between two sick cows: if gap <= 2R, they're connected.
    // 
    // So max R = minSH - epsilon. 2R ≈ 2*minSH.
    // Connect sick cows where gap < 2*minSH.
    // 
    // But this might not be optimal. Let me think again.
    // R must be < every sick-healthy adjacent distance.
    // Let bound = min of all sick-healthy adjacent distances.
    // Then 2R < 2*bound.
    // Two sick cows are connected if their distance <= 2R < 2*bound.
    // 
    // But actually, if bound is the min sick-healthy distance,
    // and there are sick-sick gaps of size >= 2*bound, those won't connect.
    // 
    // Let me implement: find bound, then connect sick cows with gap < 2*bound.
    // 
    // Actually wait. The constraint is stricter: for EACH sick-healthy pair of neighbors,
    // R < distance. So R < min_over_all_adjacent_sick_healthy(distance).
    // 
    // But if a sick cow has healthy neighbors on both sides with distances d1 and d2,
    // R < min(d1, d2).
    // 
    // So bound = min over all edges (consecutive by position) where one is sick and one healthy
    // of the distance.
    // 
    // Then connect sick cows with gap <= 2*R. Since R < bound, gap must be < 2*bound.
    // Actually gap <= 2*R < 2*bound. So gap < 2*bound (for integer gaps, gap <= 2*bound-1).
    
    // Sort by position
    vector<int> px(n), ps(n);
    for (int i = 0; i < n; i++) {
        px[i] = x[idx[i]];
        ps[i] = s[idx[i]];
    }
    
    int bound = 1000001;
    for (int i = 0; i < n - 1; i++) {
        if (ps[i] != ps[i+1]) { // one sick, one healthy
            bound = min(bound, px[i+1] - px[i]);
        }
    }
    
    // Count connected components of sick cows with gap < 2*bound
    int ans = 0;
    int lastSick = -1;
    for (int i = 0; i < n; i++) {
        if (ps[i] == 1) {
            if (lastSick == -1 || px[i] - px[lastSick] >= 2 * bound) {
                ans++;
            }
            lastSick = i;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
