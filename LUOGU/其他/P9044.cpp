#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end(), greater<int>());
    // a[0] >= a[1] >= ... >= a[n-1]
    // For each position i (0-indexed), the threshold a[i] requires giving gifts to
    // all persons with score >= a[i]. Since sorted descending, that's persons 0..j
    // where a[j] >= a[i] and (j == n-1 or a[j+1] < a[i]).
    // We want minimum such count that is >= k.
    int ans = n;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] >= a[i]) cnt++;
        }
        if (cnt >= k && cnt < ans) ans = cnt;
    }
    cout << ans << "\n";
    return 0;
}
