#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n, m;
int cake[55];
int mouth[1100];
int waste; // 当前浪费量（不能再用的小块累加）
int totalCake;

// 二分答案：能否满足前 k 张嘴
// 经典剪枝 DFS：从大到小切，当前剩余蛋糕 + 已浪费量 < 剩余嘴总和 → 失败
int target; // 当前要满足的嘴数
int needSum; // 嘴总和
int leftCake[55];

bool dfs(int idx) {
    if (idx < 0) return true;
    // 剪枝：剩余蛋糕和 - 浪费 >= 剩余需要嘴和
    // 选择把 mouth[idx] 切到某块蛋糕
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (leftCake[i] >= mouth[idx]) {
            // 相同剩余的蛋糕只试一次
            if (leftCake[i] == last) continue;
            last = leftCake[i];
            leftCake[i] -= mouth[idx];
            // 若剩余 < 最小嘴，则视为浪费
            int wasted = 0;
            if (leftCake[i] < mouth[0]) {
                wasted = leftCake[i];
                waste += wasted;
                leftCake[i] = 0;
            }
            if (waste <= totalCake - needSum) {
                if (dfs(idx - 1)) {
                    leftCake[i] += mouth[idx] + wasted;
                    waste -= wasted;
                    return true;
                }
            }
            leftCake[i] += mouth[idx] + wasted;
            waste -= wasted;
        }
    }
    return false;
}

bool check(int k) {
    // 选最小的 k 张嘴
    needSum = 0;
    for (int i = 0; i < k; ++i) needSum += mouth[i];
    if (needSum > totalCake) return false;
    for (int i = 0; i < n; ++i) leftCake[i] = cake[i];
    waste = 0;
    return dfs(k - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    totalCake = 0;
    for (int i = 0; i < n; ++i) { cin >> cake[i]; totalCake += cake[i]; }
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> mouth[i];
    sort(cake, cake + n, greater<int>());
    sort(mouth, mouth + m); // 升序
    // 去掉太大的嘴（任一蛋糕都装不下）
    int valid = 0;
    for (int i = 0; i < m; ++i) if (mouth[i] <= cake[0]) ++valid;
    // 二分
    int lo = 0, hi = valid, ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (check(mid)) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
