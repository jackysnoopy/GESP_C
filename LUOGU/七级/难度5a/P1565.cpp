#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<long long>> a(n, vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    // Prefix sum for columns
    vector<vector<long long>> ps(n + 1, vector<long long>(m, 0));
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            ps[i + 1][j] = ps[i][j] + a[i][j];
        }
    }
    
    long long ans = 0;
    
    // Try all pairs of rows
    for (int top = 0; top < n; top++) {
        for (int bottom = top; bottom < n; bottom++) {
            int height = bottom - top + 1;
            
            // For each column, compute sum of elements between top and bottom
            vector<long long> col_sum(m);
            for (int j = 0; j < m; j++) {
                col_sum[j] = ps[bottom + 1][j] - ps[top][j];
            }
            
            // Find longest subarray with average > 0, i.e., sum > 0
            // This is equivalent to finding max area rectangle with sum > 0
            // Use prefix sum and binary search
            vector<long long> prefix(m + 1, 0);
            for (int j = 0; j < m; j++) {
                prefix[j + 1] = prefix[j] + col_sum[j];
            }
            
            // For each right endpoint, find leftmost prefix that makes sum > 0
            vector<pair<long long, int>> sorted_prefix;
            for (int j = 0; j <= m; j++) {
                sorted_prefix.push_back({prefix[j], j});
            }
            sort(sorted_prefix.begin(), sorted_prefix.end());
            
            for (int j = 0; j <= m; j++) {
                // Find smallest prefix[j] - prefix[i] > 0
                // i.e., prefix[i] < prefix[j]
                // Binary search for first element < prefix[j]
                long long target = prefix[j];
                int lo = 0, hi = m + 1;
                while (lo < hi) {
                    int mid = (lo + hi) / 2;
                    if (sorted_prefix[mid].first < target) {
                        lo = mid + 1;
                    } else {
                        hi = mid;
                    }
                }
                
                if (lo > 0) {
                    int left_idx = sorted_prefix[lo - 1].second;
                    if (left_idx < j) {
                        int width = j - left_idx;
                        int area = width * height;
                        if (area > ans) {
                            ans = area;
                        }
                    }
                }
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
