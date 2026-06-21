#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, k;
long long x;
long long a[2001][2001];
bool check(long long val) {
    long long swaps = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            if (a[i][j] > val) cnt++;
        }
        swaps += cnt;
    }
    // Each swap can reduce the count by at most 2 (one from each row)
    // Actually each swap moves one element from one row to another
    // We need to move all elements > val out of each row
    // But we can swap between rows, so each swap can help 2 rows
    return swaps / 2 <= x;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    cin >> k >> x;
    // Collect all elements
    vector<long long> all;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            all.push_back(a[i][j]);
    sort(all.begin(), all.end());
    // Binary search on answer
    long long lo = 0, hi = all.size() - 1;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(all[mid])) hi = mid;
        else lo = mid + 1;
    }
    cout << all[lo] << "\n";
    return 0;
}
