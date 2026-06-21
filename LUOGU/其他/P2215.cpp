#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int m; cin >> m;
    vector<int> LIS(n, 0), dp(n, 0);
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = i;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (dp[mid] < a[i]) lo = mid + 1;
            else hi = mid;
        }
        LIS[i] = lo + 1;
        dp[lo] = a[i];
    }
    int maxLen = *max_element(LIS.begin(), LIS.end());
    while (m--) {
        int L; cin >> L;
        if (L > maxLen) { cout << "Impossible" << endl; continue; }
        vector<int> result;
        int lastVal = -1e9;
        for (int i = 0; i < n; i++) {
            if (LIS[i] == L && a[i] > lastVal) {
                result.push_back(i + 1);
                lastVal = a[i];
                L--;
                if (L == 0) break;
            }
        }
        for (int j = 0; j < (int)result.size(); j++) {
            if (j) cout << " ";
            cout << result[j];
        }
        cout << endl;
    }
    return 0;
}