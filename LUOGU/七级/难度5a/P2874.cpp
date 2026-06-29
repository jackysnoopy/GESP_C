#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    
    // Sort coordinates to find median
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    
    int median_x = x[n / 2];
    int median_y = y[n / 2];
    
    // Calculate minimum Manhattan distance sum
    long long min_dist = 0;
    for (int i = 0; i < n; i++) {
        min_dist += abs(x[i] - median_x) + abs(y[i] - median_y);
    }
    
    // Count optimal points that don't coincide with given points
    // Check all 4 possible median points
    int count = 0;
    vector<pair<int, int>> candidates = {
        {median_x, median_y},
        {median_x - 1, median_y},
        {median_x, median_y - 1},
        {median_x - 1, median_y - 1}
    };
    
    for (auto& p : candidates) {
        // Check if this point coincides with any given point
        bool coincides = false;
        for (int i = 0; i < n; i++) {
            if (x[i] == p.first && y[i] == p.second) {
                coincides = true;
                break;
            }
        }
        if (!coincides) {
            // Check if this point gives the same minimum distance
            long long dist = 0;
            for (int i = 0; i < n; i++) {
                dist += abs(x[i] - p.first) + abs(y[i] - p.second);
            }
            if (dist == min_dist) {
                count++;
            }
        }
    }
    
    cout << min_dist << " " << count << "\n";
    return 0;
}
