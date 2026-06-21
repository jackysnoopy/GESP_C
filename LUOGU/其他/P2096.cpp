#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    // For each column, compute max prefix sum across rows
    vector<int> colsum(n, 0);
    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
            colsum[j] += a[i][j];
    // Kadane's algorithm on colsum
    int maxEnding = colsum[0], maxSoFar = colsum[0];
    for (int j = 1; j < n; j++) {
        maxEnding = max(colsum[j], maxEnding + colsum[j]);
        maxSoFar = max(maxSoFar, maxEnding);
    }
    cout << maxSoFar << "\n";
    return 0;
}
