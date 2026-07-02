#include <iostream>
#include <vector>
using namespace std;

// Floyd判圈法检测循环
// 快指针走两步，慢指针走一步，相遇时在环内
// 然后让一个指针回到起点，两个都走一步，再次相遇就是环起点

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<int> f(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> f[i];
        }

        // Floyd判圈法
        int slow = 1, fast = 1;
        // 第一阶段：找到相遇点
        do {
            slow = f[slow];
            fast = f[f[fast]];
        } while (slow != fast);

        // 第二阶段：找到环起点（不动点）
        slow = 1;
        while (slow != fast) {
            slow = f[slow];
            fast = f[fast];
        }

        cout << slow << "\n";
    }
    return 0;
}
