#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 盒子结构体
struct Box {
    int id;           // 原始编号（1-indexed）
    vector<int> dims; // 排序后的维度

    // 按维度升序排序
    void sortDims() {
        sort(dims.begin(), dims.end());
    }
};

// 判断盒子a能否嵌套在盒子b中
// 条件：a的所有维度严格小于b的对应维度
bool canNest(const Box& a, const Box& b) {
    for (int i = 0; i < (int)a.dims.size(); i++) {
        if (a.dims[i] >= b.dims[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int k, n;

    // 处理多组测试数据
    // 输入格式：第一行 k n（维度数、盒子数）
    while (cin >> k >> n) {
        vector<Box> boxes(n);

        // 读取每个盒子的信息：标签 + k个维度
        for (int i = 0; i < n; i++) {
            cin >> boxes[i].id; // 读取盒子标签
            boxes[i].dims.resize(k);
            for (int j = 0; j < k; j++) {
                cin >> boxes[i].dims[j];
            }
            boxes[i].sortDims(); // 对维度排序
        }

        // 按维度字典序排序盒子
        // 排序后，如果盒子A能嵌套在盒子B中，则A一定在B之前
        sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
            for (int i = 0; i < (int)a.dims.size(); i++) {
                if (a.dims[i] != b.dims[i]) {
                    return a.dims[i] < b.dims[i];
                }
            }
            return false;
        });

        // dp[i]表示以盒子i结尾的最长嵌套链长度
        vector<int> dp(n, 1);
        // prev[i]记录前驱索引，用于路径重建
        vector<int> prev(n, -1);

        // 动态规划：求最长嵌套链
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // 如果盒子j能嵌套在盒子i中，且链长可以更新
                if (canNest(boxes[j], boxes[i]) && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }

        // 找到最长链的终点
        int maxLen = 0;
        int endIdx = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                endIdx = i;
            }
        }

        // 重建路径（从终点回溯到起点）
        vector<int> path;
        int curr = endIdx;
        while (curr != -1) {
            path.push_back(boxes[curr].id);
            curr = prev[curr];
        }

        // 反转路径，得到从小到大（从内到外）的嵌套顺序
        reverse(path.begin(), path.end());

        // 输出结果
        cout << maxLen << endl;
        for (int i = 0; i < (int)path.size(); i++) {
            if (i > 0) cout << " ";
            cout << path[i];
        }
        cout << endl;
    }

    return 0;
}
