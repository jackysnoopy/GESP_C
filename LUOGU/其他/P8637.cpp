#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> p(n);
    for (int &x : p) cin >> x;
    vector<bool> vis(n + 1, false);
    int cycles = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ++cycles;
            int j = i;
            while (!vis[j]) {
                vis[j] = true;
                j = p[j - 1];
            }
        }
    }
    cout << n - cycles << '\n';
    return 0;
}
