#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// P1007: 独木舟
// n people, boat capacity 2, weight limit w. Minimize number of boats.
// Greedy: sort, pair lightest with heaviest.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    
    int lo = 0, hi = n - 1;
    int boats = 0;
    while (lo <= hi) {
        if (lo == hi) {
            boats++;
            break;
        }
        if (a[lo] + a[hi] <= w) {
            boats++;
            lo++;
            hi--;
        } else {
            boats++;
            hi--;
        }
    }
    cout << boats << "\n";
    return 0;
}
