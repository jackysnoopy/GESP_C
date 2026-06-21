#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1005;
vector<int> children[MAXN];
int ans;
void dfs(int u, int d1, int d2) {
    int bestChild = -1;
    for (int v : children[u]) {
        if (d1 >= 0) dfs(v, d1-1, d2-1);
        else if (d2 >= 0) dfs(v, -1, d2-1);
        else { dfs(v, 2, 1); ans++; }
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 2; i <= n; i++) { int p; cin >> p; children[p].push_back(i); }
    ans = 0;
    dfs(1, -1, -1);
    cout << ans << endl;
    return 0;
}