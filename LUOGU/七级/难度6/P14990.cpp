#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 12;

int n, m, k;
int grid[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n >> m >> k;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        
        // Brute force: enumerate all subsets of rows and columns
        // For each subset, compute minimum ugliness
        
        // Ugliness = count of 2x2 submatrices that are checkerboard pattern
        // c[a][c] = c[b][d], c[b][c] = c[a][d], c[a][c] != c[a][d]
        
        long long result = 0;
        
        // Enumerate row subsets (2^n)
        for (int rowMask = 0; rowMask < (1 << n); rowMask++) {
            // For each row subset, find optimal column subset
            // This is also 2^m, too slow for n,m=12
            
            // Use meet-in-the-middle or DP
            // For now, brute force all column subsets too
            
            for (int colMask = 0; colMask < (1 << m); colMask++) {
                // Apply operations: flip selected rows and columns
                int temp[MAXN][MAXN];
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        temp[i][j] = grid[i][j];
                        if (rowMask & (1 << i)) temp[i][j] ^= 1;
                        if (colMask & (1 << j)) temp[i][j] ^= 1;
                    }
                }
                
                // Count checkerboard 2x2 submatrices
                int ugliness = 0;
                for (int i = 0; i < n - 1; i++) {
                    for (int j = 0; j < m - 1; j++) {
                        // Check if 2x2 at (i,j) is checkerboard
                        if (temp[i][j] == temp[i+1][j+1] && 
                            temp[i][j+1] == temp[i+1][j] && 
                            temp[i][j] != temp[i][j+1]) {
                            ugliness++;
                        }
                    }
                }
                
                result += (long long)ugliness * ugliness; // w(i)^k for k=1
            }
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
