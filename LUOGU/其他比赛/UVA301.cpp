#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> price;
vector<int> order;
int ans;

void dfs(int idx, int cur, vector<int>& have) {
    if (idx == n) {
        ans = max(ans, cur);
        return;
    }
    // 尝试给第idx个人他想要的三明治
    int want = order[idx];
    if (have[want] > 0) {
        have[want]--;
        dfs(idx + 1, cur + price[want], have);
        have[want]++;
    }
    // 尝试跳过这个人（不给他三明治）
    dfs(idx + 1, cur, have);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m && (n || m)) {
        price.resize(m + 1);
        for (int i = 1; i <= m; i++) cin >> price[i];
        order.resize(n);
        for (int i = 0; i < n; i++) cin >> order[i];
        ans = 0;
        vector<int> have(m + 1, 0);
        dfs(0, 0, have);
        cout << ans << "\n";
    }
    return 0;
}
