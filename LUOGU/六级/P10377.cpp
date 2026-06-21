#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    
    int ans = INT_MAX;
    do {
        int pos = 1;
        for (int i = 1; i < n; i++) {
            int gap = max(b[perm[i-1]], a[perm[i]]) + 1;
            pos += gap;
        }
        ans = min(ans, pos);
    } while (next_permutation(perm.begin(), perm.end()));
    
    cout << ans << '\n';
    
    return 0;
}
