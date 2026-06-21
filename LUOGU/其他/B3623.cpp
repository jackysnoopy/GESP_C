#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> perm;
vector<bool> used;

void dfs(int cnt) {
    if (cnt == k) {
        for (int x : perm) cout << x << " ";
        cout << "\n";
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            perm.push_back(i);
            dfs(cnt + 1);
            perm.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    used.resize(n + 1, false);
    dfs(0);
    return 0;
}