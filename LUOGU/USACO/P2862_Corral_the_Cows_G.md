# [USACO06JAN] Corral the Cows G

## 题目描述
Farmer John 希望为他的奶牛们建立一个畜栏。

这些挑剔的奶牛要求畜栏必须是正方形的，而且至少要包含 $C$ 片三叶草，来当做它们的下午茶。

约翰的土地里一共包含 $N$ 片三叶草，每单位三叶草位于一个 $1\times 1$ 的土地区域内。坐标都为整数，范围在 $1$ 到 $10000$ 以内。

**多片的三叶草可能会位于同一个 $1\times 1$ 的区域内，所以在输入内，同一个区域坐标可能出现多次。**

请你帮 Farmer John 计算一下，在能包含至少 $C$ 片三叶草的情况下，畜栏的最小边长是多少。

$1\le C\le N\le 500$。

## 输入格式
第一行两个正整数 $C,N$。

下面 $N$ 行，每行两个整数 $X,Y$，表示某一单位三叶草的位置 $(X,Y)$。

## 输出格式
一行一个整数表示答案。

## 样例
### 样例 1
```
3 4
1 2
2 1
4 1
5 2
```
```
4
```

## 提示
样例的一个最优解是，将正方形的左下角设为 $(1,1)$。

## 解题思路
### 问题分析
平面上 N 片三叶草，求包含至少 C 片的最小正方形边长。

### 核心思路
坐标范围 0~10000。二维前缀和 + 二分边长。对每个边长检查是否存在正方形满足条件。

### 算法流程
1. 读入 C, N 和三叶草坐标
2. 构建二维数组，标记有三叶草的位置
3. 计算前缀和
4. 二分边长，检查是否存在该边长的正方形包含 ≥C 片三叶草
5. 输出最小边长

### 复杂度分析
- 时间复杂度：O(MAX² log MAX)
- 空间复杂度：O(MAX²)

## 参考代码
```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10001;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C, N;
    cin >> C >> N;
    
    vector<vector<int>> a(MAXN, vector<int>(MAXN, 0));
    int max_x = 0, max_y = 0;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y]++;
        max_x = max(max_x, x);
        max_y = max(max_y, y);
    }
    
    vector<vector<int>> pre(MAXN + 1, vector<int>(MAXN + 1, 0));
    for (int i = 1; i <= MAXN; i++)
        for (int j = 1; j <= MAXN; j++)
            pre[i][j] = a[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
    
    auto sum_area = [&](int x1, int y1, int x2, int y2) {
        return pre[x2+1][y2+1] - pre[x1][y2+1] - pre[x2+1][y1] + pre[x1][y1];
    };
    
    int lo = 1, hi = 10000;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        bool ok = false;
        for (int i = 0; i + mid <= 10000 && !ok; i++) {
            for (int j = 0; j + mid <= 10000 && !ok; j++) {
                if (sum_area(i, j, i + mid - 1, j + mid - 1) >= C)
                    ok = true;
            }
        }
        if (ok) hi = mid;
        else lo = mid + 1;
    }
    
    cout << lo << "\n";
    return 0;
}
```
