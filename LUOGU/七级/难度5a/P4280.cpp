#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10005;
const int MAXK = 105;

int n, k;
int a[MAXN];
int tree[MAXK];

void update(int x, int val) {
    for (; x <= k; x += x & (-x))
        tree[x] += val;
}

int query(int x) {
    int res = 0;
    for (; x > 0; x -= x & (-x))
        res += tree[x];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) continue;
        ans += i - 1 - query(a[i]);
        update(a[i], 1);
    }
    
    cout << ans << endl;
    return 0;
}