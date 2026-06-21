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

    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int x, int y) { return a[x] < a[y]; });

    vector<bool> vis(n, false);
    int cycles = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i] || idx[i] == i) continue;
        int j = i;
        while (!vis[j]) {
            vis[j] = true;
            j = idx[j];
        }
        cycles++;
    }

    cout << n - cycles << "\n";
    return 0;
}
