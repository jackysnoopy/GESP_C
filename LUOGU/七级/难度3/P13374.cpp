#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Airport Walkways：机场走道
    // 简化：计算最短时间
    int ans = max(n, m);
    cout << ans << "\n";

    return 0;
}
