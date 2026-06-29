#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

bool canCover(vector<pair<int, int>>& points, int L) {
    int n = points.size();
    if (n == 0) return true;
    
    // Sort by x coordinate
    sort(points.begin(), points.end());
    
    // Try to cover points with 3 squares of side L
    // Strategy: cover from left to right
    int covered = 0;
    
    for (int square = 0; square < 3; square++) {
        if (covered >= n) break;
        
        // Find the rightmost point that can be covered by a square starting at points[covered].first
        int start_x = points[covered].first;
        int end_x = start_x + L;
        
        // Find all points with x <= end_x
        int rightmost = covered;
        while (rightmost + 1 < n && points[rightmost + 1].first <= end_x) {
            rightmost++;
        }
        
        // Find min and max y in this range
        int min_y = points[covered].second;
        int max_y = points[covered].second;
        for (int i = covered; i <= rightmost; i++) {
            min_y = min(min_y, points[i].second);
            max_y = max(max_y, points[i].second);
        }
        
        // Check if all points in range can be covered by a square of side L
        if (max_y - min_y <= L) {
            covered = rightmost + 1;
        } else {
            // Need to find a better split
            // Try to cover as many points as possible
            int best_cover = covered;
            for (int i = covered; i <= rightmost; i++) {
                int y_min = points[i].second;
                int y_max = points[i].second;
                for (int j = covered; j <= i; j++) {
                    y_min = min(y_min, points[j].second);
                    y_max = max(y_max, points[j].second);
                }
                if (y_max - y_min <= L) {
                    best_cover = i + 1;
                }
            }
            covered = best_cover;
        }
    }
    
    return covered >= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    
    // Binary search on L
    int low = 0, high = 2000000000;
    int answer = high;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // Make a copy for this check
        vector<pair<int, int>> pts = points;
        
        if (canCover(pts, mid)) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    cout << answer << "\n";
    return 0;
}
