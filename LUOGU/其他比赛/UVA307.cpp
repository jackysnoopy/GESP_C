#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int n;
vector<int> sticks;
vector<bool> used;
int targetLen, numSticks;

bool dfs(int stickIdx, int curLen, int startIdx) {
    if (stickIdx == numSticks) return true;
    if (curLen == targetLen) {
        return dfs(stickIdx + 1, 0, 0);
    }

    int prev = -1;
    for (int i = startIdx; i < n; i++) {
        if (used[i] || sticks[i] == prev) continue;
        if (curLen + sticks[i] > targetLen) continue;

        used[i] = true;
        if (dfs(stickIdx, curLen + sticks[i], i + 1)) return true;
        used[i] = false;
        prev = sticks[i];

        // 剪枝：第一根或当前为空则失败
        if (curLen == 0 || curLen + sticks[i] == targetLen) return false;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n != 0) {
        sticks.resize(n);
        int total = 0;
        for (int i = 0; i < n; i++) {
            cin >> sticks[i];
            total += sticks[i];
        }

        sort(sticks.rbegin(), sticks.rend());

        int ans = 0;
        for (targetLen = sticks[0]; targetLen <= total; targetLen++) {
            if (total % targetLen != 0) continue;
            numSticks = total / targetLen;
            used.assign(n, false);
            if (dfs(0, 0, 0)) {
                ans = targetLen;
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
