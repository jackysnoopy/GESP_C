#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long min_total_length(vector<int> r, vector<int> b) {
    int n = r.size(), m = b.size();
    vector<long long> dp(m + 1, 0);
    for (int i = 0; i < n; i++) {
        vector<long long> ndp(m + 1, 1e18);
        long long mn = 1e18;
        for (int j = 0; j <= m; j++) {
            if (j > 0) mn = min(mn, dp[j-1] - (long long)b[j-1]);
            ndp[j] = min(ndp[j], mn + (long long)b[j] + abs((long long)r[i] - (long long)b[j]));
        }
        dp = ndp;
    }
    long long mn = 1e18;
    for (int j = 0; j <= m; j++) mn = min(mn, dp[j]);
    return mn;
}

int main() {
    vector<int> r = {1, 2, 3, 7};
    vector<int> b = {0, 4, 5, 9, 10};
    cout << min_total_length(r, b) << endl;
    return 0;
}