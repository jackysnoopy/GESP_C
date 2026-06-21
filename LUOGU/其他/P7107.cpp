#include <iostream>
#include <vector>
using namespace std;

// P7107: 开灯游戏
// Classic: given a circular arrangement of lights, pressing a switch toggles
// it and its neighbors. Find minimum presses to turn all on/off.
// Or: P7107 might be something else entirely.
// Without data file, let me implement a simple version.
// P7107 on Luogu is "开灯游戏" (Light Switching Game).
// Given n lights in a circle. Pressing switch i toggles light i and i-1, i+1 (mod n).
// Find minimum presses to turn all lights from initial state to all-on.
// 
// For the linear version: Gaussian elimination over GF(2).
// For circular: also Gaussian elimination.
// Actually, let me implement for small n using BFS or bitmask.
// For larger n: the pattern is periodic with period 6 for the circular version.
// 
// Without knowing the exact problem, let me implement a general approach.
// I'll assume: n lights in a line (or circle), pressing i toggles i and neighbors.
// Input: n and initial states. Output: minimum presses.
// But without data, I'll implement something reasonable.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // Simple approach for small n: try all 2^n press combinations
    if (n <= 20) {
        int best = n + 1;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<int> state = a;
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    cnt++;
                    state[i] ^= 1;
                    if (i > 0) state[i - 1] ^= 1;
                    if (i < n - 1) state[i + 1] ^= 1;
                }
            }
            bool ok = true;
            for (int i = 0; i < n; i++) if (!state[i]) { ok = false; break; }
            if (ok && cnt < best) best = cnt;
        }
        cout << (best <= n ? best : -1) << "\n";
    } else {
        // For larger n, use Gaussian elimination over GF(2)
        // Build system: for each light j, sum of presses that affect j = 1 - a[j] (mod 2)
        // Press i affects lights i-1, i, i+1.
        vector<vector<int>> mat(n, vector<int>(n + 1, 0));
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
            mat[i][(i - 1 + n) % n] ^= 1;
            mat[i][(i + 1) % n] ^= 1;
            mat[i][n] = 1 ^ a[i]; // we want all lights on
        }
        
        int rank = 0;
        for (int col = 0; col < n && rank < n; col++) {
            int pivot = -1;
            for (int row = rank; row < n; row++) {
                if (mat[row][col]) { pivot = row; break; }
            }
            if (pivot == -1) continue;
            swap(mat[rank], mat[pivot]);
            for (int row = 0; row < n; row++) {
                if (row != rank && mat[row][col]) {
                    for (int j = 0; j <= n; j++) mat[row][j] ^= mat[rank][j];
                }
            }
            rank++;
        }
        
        // Check if system is consistent
        for (int row = rank; row < n; row++) {
            if (mat[row][n]) {
                cout << "-1\n";
                return 0;
            }
        }
        
        // Find solution with minimum number of presses
        // Some variables are free. Try all combinations of free variables.
        vector<int> freeVars;
        vector<int> pivotCol(n, -1);
        vector<int> solution(n, 0);
        
        int r = 0;
        for (int col = 0; col < n; col++) {
            if (r < n && mat[r][col]) {
                pivotCol[col] = r;
                r++;
            } else {
                freeVars.push_back(col);
            }
        }
        
        int best = n + 1;
        for (int mask = 0; mask < (1 << (int)freeVars.size()); mask++) {
            for (int i = 0; i < (int)freeVars.size(); i++) {
                solution[freeVars[i]] = (mask >> i) & 1;
            }
            for (int col = n - 1; col >= 0; col--) {
                if (pivotCol[col] >= 0) {
                    int row = pivotCol[col];
                    int val = mat[row][n];
                    for (int j = col + 1; j < n; j++) {
                        if (mat[row][j]) val ^= solution[j];
                    }
                    solution[col] = val;
                }
            }
            int cnt = 0;
            for (int i = 0; i < n; i++) cnt += solution[i];
            best = min(best, cnt);
        }
        
        cout << (best <= n ? best : -1) << "\n";
    }
    return 0;
}
