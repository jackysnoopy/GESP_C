#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;
vector<int> cake, mouth;
bool dfs(int ci, int mi, int target) {
    if (mi == target) return true;
    if (ci == n) return false;
    if (cake[ci] >= mouth[mi]) {
        cake[ci] -= mouth[mi];
        if (dfs(ci, mi+1, target)) { cake[ci] += mouth[mi]; return true; }
        cake[ci] += mouth[mi];
    }
    return dfs(ci+1, mi, target);
}
bool check(int k) {
    vector<int> tc = cake;
    bool r = dfs(0, 0, k);
    cake = tc;
    return r;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    cake.resize(n);
    for (int i = 0; i < n; i++) cin >> cake[i];
    cin >> m;
    mouth.resize(m);
    for (int i = 0; i < m; i++) cin >> mouth[i];
    sort(cake.begin(), cake.end(), greater<int>());
    sort(mouth.begin(), mouth.end());
    int lo = 0, hi = m;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid; else hi = mid - 1;
    }
    cout << lo << endl;
    return 0;
}