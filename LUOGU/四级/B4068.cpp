#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_set<int> seen;
    a[0] = 1;
    seen.insert(1);
    for (int k = 2; k <= n; k++) {
        int cand = a[k - 2] - k;
        if (cand > 0 && !seen.count(cand)) {
            a[k - 1] = cand;
        } else {
            a[k - 1] = a[k - 2] + k;
        }
        seen.insert(a[k - 1]);
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    return 0;
}
