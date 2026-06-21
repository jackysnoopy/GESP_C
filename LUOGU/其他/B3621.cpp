#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> a;

void dfs(int pos) {
    if (pos > n) {
        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << " ";
            cout << a[i];
        }
        cout << "\n";
        return;
    }
    for (int val = 1; val <= k; val++) {
        a[pos] = val;
        dfs(pos + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    a.resize(n + 1);
    dfs(1);
    return 0;
}