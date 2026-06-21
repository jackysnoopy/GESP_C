#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ull> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    // Sort a, assign smallest b to largest increments
    vector<ull> va(a.begin(), a.end());
    sort(va.begin(), va.end());
    vector<ull> vb(b.begin(), b.end());
    sort(vb.begin(), vb.end());
    ull ans = 0;
    // Each element a[i] needs to become unique
    // After sorting a: va[0] <= va[1] <= ... <= va[n-1]
    // Each va[i] must be >= va[i-1]+1 ideally
    ull cur = 0;
    for (int i = 0; i < n; i++) {
        cur = max(cur, va[i]);
        ull need = (i > 0) ? cur - va[i] + 1 : 0;
        // Actually: va[i] needs to be at least i + min_value
        // After sorting, assign: the i-th smallest gets incremented to be distinct
        // Increment for va[i] = max(0, target - va[i]) where target increases
        ull target = (i == 0) ? va[0] : max(cur + 1, va[i]);
        ull inc = (target > va[i]) ? target - va[i] : 0;
        cur = va[i] + inc;
        // Match increment with cheapest b
    }
    // Simpler: sort both, greedily assign
    // For each a value that needs increment, use the smallest available b
    vector<ull> incs;
    cur = 0;
    for (int i = 0; i < n; i++) {
        ull target = (i == 0) ? va[0] : max(cur + 1, va[i]);
        if (target > va[i]) incs.push_back(target - va[i]);
        cur = target;
    }
    sort(incs.rbegin(), incs.rend());
    sort(vb.begin(), vb.end());
    for (int i = 0; i < (int)incs.size() && i < n; i++)
        ans += incs[i] * vb[i];
    cout << ans << "\n";
    return 0;
}
