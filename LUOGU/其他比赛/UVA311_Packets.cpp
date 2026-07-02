#include <iostream>
#include <algorithm>
using namespace std;

int cnt[7];

int solve() {
    int boxes = 0;
    while (true) {
        bool done = true;
        for (int i = 1; i <= 6; i++) {
            if (cnt[i] > 0) { done = false; break; }
        }
        if (done) break;
        boxes++;

        if (cnt[6] > 0) { cnt[6]--; continue; }
        if (cnt[5] > 0) {
            cnt[5]--;
            int space = 11;
            space -= min(cnt[1], space);
            continue;
        }
        if (cnt[4] > 0) {
            cnt[4]--;
            int space = 5;
            int take2 = min(cnt[2], space);
            cnt[2] -= take2;
            space -= take2 * 4;
            int take1 = min(cnt[1], space);
            cnt[1] -= take1;
            continue;
        }
        if (cnt[3] > 0) {
            int take3 = min(cnt[3], 4);
            cnt[3] -= take3;
            int remain = 4 - take3;
            int space = 0;
            if (remain == 3) space = 1;
            else if (remain == 2) space = 3;
            else if (remain == 1) space = 5;
            if (space > 0) {
                int take2 = min(cnt[2], space);
                cnt[2] -= take2;
                space -= take2 * 4;
                space = max(space, 0);
                int take1 = min(cnt[1], space);
                cnt[1] -= take1;
            }
            continue;
        }
        if (cnt[2] > 0) {
            int take2 = min(cnt[2], 9);
            cnt[2] -= take2;
            int space = (9 - take2) * 4;
            int take1 = min(cnt[1], space);
            cnt[1] -= take1;
            continue;
        }
        if (cnt[1] > 0) {
            int take1 = min(cnt[1], 36);
            cnt[1] -= take1;
        }
    }
    return boxes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        bool hasItem = false;
        for (int i = 1; i <= 6; i++) {
            cin >> cnt[i];
            if (cnt[i] > 0) hasItem = true;
        }
        if (!hasItem) break;
        cout << solve() << "\n";
    }
    return 0;
}
