#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int w, n;
    cin >> w >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int l = 0, r = n - 1, groups = 0;
    while (l <= r) {
        if (a[l] + a[r] <= w) { l++; r--; }
        else r--;
        groups++;
    }
    cout << groups << "\n";
    return 0;
}
