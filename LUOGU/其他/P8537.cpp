#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    // Option 1: no reverse. Count of different elements.
    int cnt1 = 0;
    for (int i = 0; i < n; i++) if (a[i] != b[i]) cnt1++;
    // Option 2: reverse a first, then count differences.
    int cnt2 = 0;
    for (int i = 0; i < n; i++) if (a[n-1-i] != b[i]) cnt2++;
    // Answer = min(cnt1, 1+cnt2)
    cout << min(cnt1, 1 + cnt2) << "\n";
    return 0;
}
