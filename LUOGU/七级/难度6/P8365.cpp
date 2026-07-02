#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 500005;
int a[MAXN], b[MAXN];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    // Sort by a[i] descending
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int x, int y) {
        return a[x] > a[y];
    });
    
    long long ans = 1;
    long long sum = 0;
    
    for (int i = 0; i < n; i++) {
        int id = idx[i];
        // Choose operation: multiply by a[id] or add b[id]
        if (a[id] > 1 && sum * (a[id] - 1) > b[id]) {
            ans = ans * a[id] % MOD;
        } else {
            sum += b[id];
            ans = (ans + b[id]) % MOD;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}