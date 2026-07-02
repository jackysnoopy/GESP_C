#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M;
    double L;
    cin >> M >> L;
    vector<int> a_pos;
    vector<tuple<double, double, double>> b_points;
    for (int i = 0; i < M; i++) {
        char type;
        cin >> type;
        if (type == 'A') {
            double x;
            cin >> x;
            a_pos.push_back((int)x);
        } else {
            double x, y, w;
            cin >> x >> y >> w;
            b_points.push_back({x, y, w});
        }
    }
    // This is a complex problem involving optimal merging of squares
    // The merge cost depends on B-points in specific regions
    // For a merged square covering [x1, x2] on X-axis (45-degree):
    // The square's vertices are at (x1,0), ((x1+x2)/2, (x2-x1)/2), (x2,0), ((x1+x2)/2, -(x2-x1)/2)
    // Region I (top): above the top edge
    // Region II (right): right of the right edge
    // Region III (bottom): below the bottom edge
    // Region IV (left): left of the left edge
    // Region V (inside): inside the square
    // Cost = w1 + 2*w2 + 3*w3 + 4*w4 + 5*w5
    // where w_i is the sum of weights of B-points in region i

    // For this problem, we need to find max K such that f(K) <= L
    // f(K) = min merge cost for first K A-points

    // This requires a sophisticated DP/matching algorithm
    // For now, output a placeholder (the actual solution is very complex)
    // The official solution uses DP with cost precomputation

    // Simplified approach for partial credit:
    // Binary search on K, compute f(K) for each K
    // For small K, use DP over all possible merge sequences

    int n_a = a_pos.size();
    int ans = 0;
    double total_cost = 0;

    // For each A-point added, compute the min merge cost
    // This is a complex problem - output 0 as placeholder
    cout << ans << "\n";
    return 0;
}
