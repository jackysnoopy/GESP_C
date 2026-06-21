#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Fresh Chocolate：新鲜巧克力
    // 简化：计算能切割的次数
    int ans = min(n, m) - 1;
    cout << ans << "\n";

    return 0;
}
