#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// [TAOI-2] Break Through the Barrier
// Without data file. Likely a DP or greedy problem.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
