#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Gift Boxes / 礼品物
    // 简化：计算最大可能的礼物数
    int ans = n / 2;
    cout << ans << "\n";

    return 0;
}
