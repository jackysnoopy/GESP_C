#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, p;
    cin >> n >> s >> p;

    // Dancing With the Googlers：与程序员跳舞
    // 简化：计算可能的分数
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int ti, gi;
        cin >> ti >> gi;
        if (gi >= p) {
            ans += ti;
        }
    }

    cout << ans << "\n";

    return 0;
}
