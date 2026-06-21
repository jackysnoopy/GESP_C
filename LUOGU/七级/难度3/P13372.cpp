#include <iostream>
#include. <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    // Space Emergency：太空紧急情况
    // 简化：计算时间
    int ans = (n + m) / t;
    cout << ans << "\n";

    return 0;
}
