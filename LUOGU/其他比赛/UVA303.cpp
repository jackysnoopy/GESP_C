#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Ant {
    int id;
    int pos;
    int dir; // 1: right, -1: left
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, n;
    while (cin >> L >> n) {
        vector<Ant> ants(n);
        for (int i = 0; i < n; i++) {
            char d;
            cin >> ants[i].pos >> d;
            ants[i].id = i;
            ants[i].dir = (d == 'R' ? 1 : -1);
        }

        // 关键观察：相遇掉头等价于互相穿过
        // 每只蚂蚁的最终位置 = 模拟穿过时的位置
        // 排序后，第i只从左边穿过的蚂蚁位置就是排序后第i个位置

        vector<int> leftPos, rightPos;
        for (int i = 0; i < n; i++) {
            if (ants[i].dir == 1) {
                leftPos.push_back(ants[i].pos);
            } else {
                rightPos.push_back(ants[i].pos);
            }
        }
        sort(leftPos.begin(), leftPos.end());
        sort(rightPos.begin(), rightPos.end());

        vector<int> result(n);
        // 从左穿过的蚂蚁，按位置排序
        for (int i = 0; i < (int)leftPos.size(); i++) {
            result[i] = leftPos[i];
        }
        // 从右穿过的蚂蚁，按位置从大到小
        int idx = leftPos.size();
        for (int i = (int)rightPos.size() - 1; i >= 0; i--) {
            result[idx++] = L - rightPos[i];
        }

        // 输出
        for (int i = 0; i < n; i++) {
            cout << result[i];
            if (i < n - 1) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
