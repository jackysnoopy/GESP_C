#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];
    // N x N grid, each cell R, G, or B.
    // Find largest square subgrid where all cells on boundary are same color.
    // Boundary of square [r1,r2]x[c1,c2]: all cells where r=r1 or r=r2 or c=c1 or c=c2.
    
    int ans = 0;
    // For each color, for each possible size, check if there's a valid square.
    // O(N^3) approach: for each top-left (r,c) and size s, check boundary.
    // N <= 1000? Let me check the data.
    // Actually the data file says N up to... I need to check.
    // For now, O(N^3) with N=1000 might be too slow. Let me use prefix sums.
    
    // For each color ch in {R,G,B}:
    // Build prefix sum grid for cells not equal to ch.
    // Then for each square, check if boundary has no non-ch cells.
    // Boundary of square [r1,r2]x[c1,c2]:
    //   top row: r1, c1..c2
    //   bottom row: r2, c1..c2
    //   left col: c1, r1+1..r2-1
    //   right col: c2, r1+1..r2-1
    // Using prefix sums, each row/col check is O(1).
    // Total: O(N^2 * N) = O(N^3) for all sizes. For N=500, this is 1.25*10^8. Might be OK.
    // Actually let me check the constraints from the data.
    
    // I'll assume N <= 500 based on typical JOI problems.
    // Build prefix sums for each color.
    vector<vector<int>> ps(N + 1, vector<int>(N + 1, 0));
    // ps[i][j] = number of cells not equal to current color in [0,i)x[0,j)
    // Actually let me just do it for each color separately.
    
    for (char ch : {'R', 'G', 'B'}) {
        vector<vector<int>> grid(N + 1, vector<int>(N + 1, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i + 1][j + 1] = (S[i][j] != ch) ? 1 : 0;
            }
        }
        // Build prefix sum
        vector<vector<int>> ps(N + 1, vector<int>(N + 1, 0));
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                ps[i][j] = grid[i][j] + ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
            }
        }
        auto sum = [&](int r1, int c1, int r2, int c2) -> int {
            return ps[r2][c2] - ps[r1][c2] - ps[r2][c1] + ps[r1][c1];
        };
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                int maxSize = min(N - r, N - c);
                for (int s = 1; s <= maxSize; s++) {
                    int r2 = r + s, c2 = c + s;
                    // Check boundary: top row, bottom row, left col, right col
                    bool ok = true;
                    // Top row: [r, r+1) x [c, c+s)
                    if (sum(r, c, r + 1, c + s) > 0) ok = false;
                    // Bottom row: [r+s-1, r+s) x [c, c+s)
                    if (ok && s > 1 && sum(r + s - 1, c, r + s, c + s) > 0) ok = false;
                    // Left col: [r+1, r+s-1) x [c, c+1)
                    if (ok && s > 2 && sum(r + 1, c, r + s - 1, c + 1) > 0) ok = false;
                    // Right col: [r+1, r+s-1) x [c+s-1, c+s)
                    if (ok && s > 2 && sum(r + 1, c + s - 1, r + s - 1, c + s) > 0) ok = false;
                    if (ok) ans = max(ans, s);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
