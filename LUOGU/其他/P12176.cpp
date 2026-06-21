#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<bool> vis(n, false);
    int cycles = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cycles++;
            int j = i;
            while (!vis[j]) {
                vis[j] = true;
                j = a[j] - 1;
            }
        }
    }
    cout << n - cycles << "\n";
    return 0;
}
