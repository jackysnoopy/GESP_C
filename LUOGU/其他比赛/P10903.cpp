#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> l(m+1), r(m+1), d(n+2, 0);
    for (int i = 1; i <= m; i++) {
        cin >> l[i] >> r[i];
        d[l[i]]++; d[r[i]+1]--;
    }
    vector<int> cnt(n+1, 0);
    int zero = 0;
    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i-1] + d[i];
        if (cnt[i] == 0) zero++;
    }
    vector<int> one(n+1, 0);
    for (int i = 1; i <= n; i++) one[i] = one[i-1] + (cnt[i] == 1);
    for (int i = 1; i <= m; i++) {
        int c = one[r[i]] - one[l[i] - 1];
        cout << zero + c << "\n";
    }
    return 0;
}
