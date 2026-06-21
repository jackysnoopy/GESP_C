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
    sort(a.begin(), a.end());
    long long sum = 0, ans = 0;
    for (int l = 0, r = 0; r < n; r++) {
        sum += a[r];
        while (a[r] - a[l] > k) {
            sum -= a[l];
            l++;
        }
        if (sum > ans) ans = sum;
    }
    cout << ans << "\n";
    return 0;
}
