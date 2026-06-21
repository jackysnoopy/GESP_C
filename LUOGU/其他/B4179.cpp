#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, n;
    cin >> k >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    if (k >= n) { cout << 0 << "\n"; return 0; }
    vector<int> gaps;
    for (int i = 1; i < n; i++) gaps.push_back(a[i] - a[i-1] - 1);
    sort(gaps.begin(), gaps.end(), greater<int>());
    int total = a[n-1] - a[0] + 1;
    for (int i = 0; i < k - 1 && i < (int)gaps.size(); i++) total -= gaps[i];
    cout << total << "\n";
    return 0;
}
