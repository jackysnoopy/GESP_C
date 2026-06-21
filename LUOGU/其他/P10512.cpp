#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// P10512: 序列合并
// Merge two sorted sequences. Without data file.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    
    vector<int> result;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) { result.push_back(a[i]); i++; }
        else { result.push_back(b[j]); j++; }
    }
    while (i < n) { result.push_back(a[i]); i++; }
    while (j < m) { result.push_back(b[j]); j++; }
    
    for (int k = 0; k < (int)result.size(); k++) {
        cout << result[k] << (k + 1 < (int)result.size() ? " " : "\n");
    }
    return 0;
}
