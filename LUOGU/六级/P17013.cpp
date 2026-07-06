#include <iostream>
#include <vector>
using namespace std;

vector<int> lch, rch;
int ans = 0;

int dfs(int u) {
    if (u == 0) return -1;
    
    int leftDep = dfs(lch[u]);
    int rightDep = dfs(rch[u]);
    
    if (lch[u] == 0 && rch[u] == 0) {
        ans++;
        return 0;
    }
    
    if (lch[u] != 0 && rch[u] != 0 && leftDep >= 0 && rightDep >= 0 && leftDep == rightDep) {
        ans++;
        return leftDep + 1;
    }
    
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    lch.resize(n + 1);
    rch.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> lch[i] >> rch[i];
    }

    dfs(1);
    cout << ans << endl;
    return 0;
}
