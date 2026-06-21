#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> posJ, posO, posI;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'J') posJ.push_back(i);
        else if (s[i] == 'O') posO.push_back(i);
        else posI.push_back(i);
    }
    int totalJ = posJ.size(), totalO = posO.size(), totalI = posI.size();
    if (totalJ < k || totalO < k || totalI < k) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> oPrefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        oPrefix[i + 1] = oPrefix[i] + (s[i] == 'O' ? 1 : 0);
    }
    auto oCount = [&](int l, int r) -> int {
        if (l > r) return 0;
        return oPrefix[r + 1] - oPrefix[l];
    };
    int ans = n;
    for (int b = 0; b + k <= totalI; b++) {
        int iStart = posI[b];
        int iEnd = posI[b + k - 1];
        int lo = 0, hi = totalJ - k, bestA = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int jEnd = posJ[mid + k - 1];
            if (jEnd >= iStart) {
                hi = mid - 1;
                continue;
            }
            int oc = oCount(jEnd + 1, iStart - 1);
            if (oc >= k) {
                bestA = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (bestA >= 0) {
            int l = posJ[bestA];
            int r = iEnd;
            ans = min(ans, r - l + 1 - 3 * k);
        }
    }
    if (ans == n) ans = -1;
    cout << ans << endl;
    return 0;
}
