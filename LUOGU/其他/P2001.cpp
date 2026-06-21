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
    // Coin change: min coins to make each value 1..X
    // But this problem is "硬币的面值" - find min number of coins to make 1..X
    // Actually this is: given coin denominations, find minimum coins to represent all values
    // Greedy: sort, check if sorted coins can make all values up to max
    sort(a.begin(), a.end());
    if (a[0] != 1) { cout << -1 << "\n"; return 0; }
    long long reach = 0;
    for (int i = 0; i < n && a[i] <= reach + 1; i++) reach += a[i];
    cout << reach << "\n";
    return 0;
}
