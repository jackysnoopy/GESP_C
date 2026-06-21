#include <iostream>
#include <vector>
using namespace std;

// P10059: Choose
// Without data file. Implementing a basic selection problem.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // Choose k elements to maximize sum
    sort(a.begin(), a.end(), greater<int>());
    long long ans = 0;
    for (int i = 0; i < k; i++) ans += a[i];
    cout << ans << "\n";
    return 0;
}
