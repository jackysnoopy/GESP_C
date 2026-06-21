#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

long long calc(vector<int>& a, int avg) {
    int n = a.size();
    vector<long long> pre(n);
    pre[0] = a[0] - avg;
    for (int i = 1; i < n; i++)
        pre[i] = pre[i-1] + a[i] - avg;
    sort(pre.begin(), pre.end());
    long long mid = pre[n/2], ans = 0;
    for (long long x : pre) ans += abs(x - mid);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, T;
    cin >> N >> M >> T;
    
    vector<int> row(N, 0), col(M, 0);
    for (int i = 0; i < T; i++) {
        int x, y;
        cin >> x >> y;
        row[x-1]++;
        col[y-1]++;
    }
    
    bool can_row = (T % N == 0);
    bool can_col = (T % M == 0);
    
    if (!can_row && !can_col) {
        cout << "impossible\n";
        return 0;
    }
    
    if (can_row && can_col) {
        cout << "both " << calc(row, T/N) + calc(col, T/M) << "\n";
    } else if (can_row) {
        cout << "row " << calc(row, T/N) << "\n";
    } else {
        cout << "column " << calc(col, T/M) << "\n";
    }
    
    return 0;
}