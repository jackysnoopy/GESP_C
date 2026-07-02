#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M, K;
        cin >> N >> M >> K;
        
        cout << "Case #" << t << ": ";
        
        // Greedy: try diamond shapes centered at corners, then fill
        // For the small dataset (N*M <= 20), we can use DP
        // For large, use greedy formula
        
        int ans = K; // worst case: K stones for K points
        
        // Try all possible rectangular enclosures
        for (int r1 = 0; r1 < N; r1++) {
            for (int c1 = 0; c1 < M; c1++) {
                for (int r2 = r1; r2 < N; r2++) {
                    for (int c2 = c1; c2 < M; c2++) {
                        // Perimeter stones needed = 2*(r2-r1+1) + 2*(c2-c1+1) - 4
                        int perimeter = 2 * (r2 - r1 + 1) + 2 * (c2 - c1 + 1) - 4;
                        int inner = (r2 - r1 - 1) * (c2 - c1 - 1);
                        if (r2 - r1 <= 1 || c2 - c1 <= 1) inner = 0;
                        int enclosed = inner + perimeter;
                        if (enclosed >= K) {
                            ans = min(ans, perimeter);
                        }
                    }
                }
            }
        }
        
        // Also try diamond shapes
        // For each center, try increasing diamond sizes
        for (int cr = 0; cr < N; cr++) {
            for (int cc = 0; cc < M; cc++) {
                for (int d = 0; d <= N + M; d++) {
                    int stones = 0;
                    int enclosed = 0;
                    for (int r = 0; r < N; r++) {
                        for (int c = 0; c < M; c++) {
                            if (abs(r - cr) + abs(c - cc) <= d) {
                                enclosed++;
                                if (abs(r - cr) + abs(c - cc) == d) stones++;
                            }
                        }
                    }
                    if (d == 0) stones = 1;
                    if (enclosed >= K) {
                        ans = min(ans, stones);
                        break;
                    }
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}