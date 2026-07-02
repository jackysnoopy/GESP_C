#include <iostream>
#include <vector>
using namespace std;

// 预计算：对于给定的n，求最小的k使得位置1的人总是最后一个被杀
// 暴力枚举k值，模拟约瑟夫过程

int simulate(int n, int k) {
    vector<int> circle;
    for (int i = 1; i <= n; i++) {
        circle.push_back(i);
    }

    int pos = 0; // 从位置0开始
    while (circle.size() > 1) {
        // 数k个人，杀死第k个
        pos = (pos + k - 1) % circle.size();
        circle.erase(circle.begin() + pos);
        // 杀死后从下一个位置继续
    }

    return circle[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        // 枚举k值，找到使位置1最后存活的最小k
        for (int k = 1; ; k++) {
            if (simulate(n, k) == 1) {
                cout << k << "\n";
                break;
            }
        }
    }
    return 0;
}
