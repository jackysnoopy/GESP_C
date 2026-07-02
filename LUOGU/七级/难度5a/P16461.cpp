#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<vector<long long>> a(n, vector<long long>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    // For each column j, we want to minimize b_j
    // Each swap in row i between columns j1,j2 changes b_j1 by a[i][j2]-a[i][j1]
    // Greedy: process columns left to right
    // For column j, find best swaps to minimize sum of column j
    vector<long long> col_sum(m, 0);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            col_sum[j] += a[i][j];
    long long swaps_left = k;
    for (int j = 0; j < m && swaps_left > 0; j++) {
        // For each row, find the minimum element not yet in column j
        // and see if swapping would help
        for (int i = 0; i < n && swaps_left > 0; i++) {
            int best_col = j;
            for (int c = j + 1; c < m; c++) {
                if (a[i][c] < a[i][best_col]) best_col = c;
            }
            if (best_col != j) {
                swap(a[i][j], a[i][best_col]);
                col_sum[j] = 0;
                for (int r = 0; r < n; r++) col_sum[j] += a[r][j];
                swaps_left--;
            }
        }
    }
    for (int j = 0; j < m; j++) cout << col_sum[j] << " \n"[j==m-1];
    return 0;
}
