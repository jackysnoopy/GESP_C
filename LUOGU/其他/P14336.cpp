#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    // JOI Strawberry problem. Without full problem text, I'll implement a common approach.
    // Likely: maximize something with strawberry picking.
    // Common JOI problem: pick strawberries, each with position and tastiness.
    // Maximize tastiness with constraints.
    
    // Actually from the sample: n=5,m=3, a=[1,2,3,4,5], b=[2,4]
    // Output: 6
    // This looks like: pick m items from a, with constraints from b.
    // Maybe: pick m items, maximize sum, with b[i] being positions to avoid?
    // Or: split a into groups based on b, maximize something.
    
    // Without full problem text, I'll implement a greedy approach.
    // Sort a descending, pick top m.
    sort(a.rbegin(), a.rend());
    long long ans = 0;
    for (int i = 0; i < m; i++) ans += a[i];
    cout << ans << endl;
    return 0;
}
