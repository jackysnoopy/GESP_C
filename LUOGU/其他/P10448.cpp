#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> chosen;

void dfs(int start, int cnt) {
    if (cnt == m) {
        for (int x : chosen) cout << x << " ";
        cout << "\n";
        return;
    }
    for (int i = start; i <= n; i++) {
        chosen.push_back(i);
        dfs(i + 1, cnt + 1);
        chosen.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    dfs(1, 0);
    return 0;
}