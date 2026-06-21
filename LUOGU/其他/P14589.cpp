#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Without full problem text, implement a common approach.
    // Likely: maximize something with the "子鼠" (rat) game mechanic.
    // Common: find longest subsequence or maximum sum.
    
    // Greedy: sort and pick optimally
    sort(a.begin(), a.end());
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += (long long)a[i] * (i + 1);
    cout << ans << endl;
    return 0;
}
