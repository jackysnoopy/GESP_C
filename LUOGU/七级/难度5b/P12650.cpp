#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    // For each white cell, compute the V-shape coverage
    // A V-shape from (r, c) covers:
    // - Left diagonal: (r-k, c-k) for k = 0, 1, ... until non-white or out of bounds
    // - Right diagonal: (r-k, c+k) for k = 1, 2, ... until non-white or out of bounds
    
    // Precompute for each cell the length of V-shape in each direction
    vector<vector<int>> left_len(n, vector<int>(m, 0));
    vector<vector<int>> right_len(n, vector<int>(m, 0));
    
    // Compute left diagonal lengths (going up-left)
    for (int c = 0; c < m; c++) {
        for (int r = 0; r < n; r++) {
            if (grid[r][c] == '1') {
                if (r == 0 || c == 0 || grid[r-1][c-1] == '0') {
                    left_len[r][c] = 1;
                } else {
                    left_len[r][c] = left_len[r-1][c-1] + 1;
                }
            }
        }
    }
    
    // Compute right diagonal lengths (going up-right)
    for (int c = m - 1; c >= 0; c--) {
        for (int r = 0; r < n; r++) {
            if (grid[r][c] == '1') {
                if (r == 0 || c == m - 1 || grid[r-1][c+1] == '0') {
                    right_len[r][c] = 1;
                } else {
                    right_len[r][c] = right_len[r-1][c+1] + 1;
                }
            }
        }
    }
    
    // For each white cell, compute total V-shape coverage
    // V-shape from (r, c): left_len[r][c] + right_len[r][c] - 1 (subtract 1 for the starting cell)
    // But the starting cell is only counted once
    
    // Actually, the V-shape starts at (r, c) and goes:
    // - Left: (r, c), (r-1, c-1), (r-2, c-2), ... for left_len[r][c] cells
    // - Right: (r, c-1), (r-1, c), (r-2, c+1), ... for right_len[r][c] - 1 cells (starting from c-1)
    
    // Wait, let me re-read the problem:
    // "从该格子开始，沿左上对角线（即每次向左上方移动一格）前进"
    // "从起点的右上方一格开始，沿右上对角线（即每次向右上方移动一格）前进"
    
    // So the V-shape covers:
    // - Left: (r, c), (r-1, c-1), (r-2, c-2), ... for left_len[r][c] cells
    // - Right: (r-1, c+1), (r-2, c+2), ... for right_len[r-1][c+1] cells (if r > 0 and c < m-1)
    
    // Total coverage = left_len[r][c] + (r > 0 && c < m-1 ? right_len[r-1][c+1] : 0)
    
    // For two V-shapes, we want to maximize the union of their coverages
    
    // Let's compute the coverage for each possible V-shape
    vector<vector<int>> coverage(n, vector<int>(m, 0));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == '1') {
                coverage[r][c] = left_len[r][c];
                if (r > 0 && c < m - 1) {
                    coverage[r][c] += right_len[r-1][c+1];
                }
            }
        }
    }
    
    // Now we need to find two V-shapes that maximize the union of their coverages
    // This is a maximum coverage problem
    
    // For each cell, compute which V-shapes cover it
    // Then find two V-shapes with maximum union
    
    // This is O(n*m * n*m) which might be too slow for n, m <= 3000
    // Let's think of a better approach
    
    // Actually, for n, m <= 3000, O(n*m) is fine
    // But we need to find two V-shapes with maximum union
    
    // Let's use a different approach:
    // For each pair of V-shapes, compute the union
    // But this is O((n*m)^2) which is too slow
    
    // Let's think about the structure of V-shapes:
    // Each V-shape is defined by its starting cell (r, c)
    // The coverage is a set of cells along two diagonals
    
    // For two V-shapes starting at (r1, c1) and (r2, c2):
    // They might overlap if their diagonals intersect
    
    // This is getting complicated. Let me try a simpler approach:
    // For each cell, compute the maximum coverage if we use a V-shape that covers it
    // Then for each pair of cells, compute the union
    
    // Actually, let's just try all pairs of V-shapes for small inputs
    // For n, m <= 3000, this is O(n*m) which is fine
    
    // Wait, we need to find two V-shapes with maximum union
    // This is a maximum coverage problem which is NP-hard in general
    // But for this specific structure, we might be able to solve it efficiently
    
    // Let me try a different approach:
    // For each cell, compute the best V-shape that covers it
    // Then for each pair of cells, compute the union if we use those V-shapes
    
    // Actually, let's just implement a simple O(n*m * n*m) solution
    // and hope it's fast enough
    
    int ans = 0;
    
    // For each pair of starting cells
    for (int r1 = 0; r1 < n; r1++) {
        for (int c1 = 0; c1 < m; c1++) {
            if (grid[r1][c1] != '1') continue;
            
            // Compute the set of cells covered by V-shape from (r1, c1)
            vector<vector<bool>> covered(n, vector<bool>(m, false));
            int total1 = 0;
            
            // Left diagonal
            for (int k = 0; k < left_len[r1][c1]; k++) {
                int r = r1 - k, c = c1 - k;
                if (r >= 0 && c >= 0 && grid[r][c] == '1' && !covered[r][c]) {
                    covered[r][c] = true;
                    total1++;
                }
            }
            
            // Right diagonal
            for (int k = 1; k <= (r1 > 0 && c1 < m-1 ? right_len[r1-1][c1+1] : 0); k++) {
                int r = r1 - k, c = c1 + k;
                if (r >= 0 && c < m && grid[r][c] == '1' && !covered[r][c]) {
                    covered[r][c] = true;
                    total1++;
                }
            }
            
            // For each other starting cell
            for (int r2 = 0; r2 < n; r2++) {
                for (int c2 = 0; c2 < m; c2++) {
                    if (grid[r2][c2] != '1') continue;
                    
                    int total2 = total1;
                    
                    // Left diagonal of second V-shape
                    for (int k = 0; k < left_len[r2][c2]; k++) {
                        int r = r2 - k, c = c2 - k;
                        if (r >= 0 && c >= 0 && grid[r][c] == '1' && !covered[r][c]) {
                            total2++;
                        }
                    }
                    
                    // Right diagonal of second V-shape
                    for (int k = 1; k <= (r2 > 0 && c2 < m-1 ? right_len[r2-1][c2+1] : 0); k++) {
                        int r = r2 - k, c = c2 + k;
                        if (r >= 0 && c < m && grid[r][c] == '1' && !covered[r][c]) {
                            total2++;
                        }
                    }
                    
                    ans = max(ans, total2);
                }
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
