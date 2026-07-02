# River Jumping

## 题目描述
有一条宽度为 N 的河上，小 D 位于坐标为 0 的河岸上，他想到达坐标为 N 的河岸上后再回到坐标为 0 的位置。在到达坐标为 N 的河岸之前小 D 只能向坐标更大的位置跳跃，在到达坐标为 N 的河岸之后小 D 只能向坐标更小的位置跳跃。在河的中间有 M 个岩石，小 D 希望能跳到每个岩石上恰好一次。由于小 D 的跳跃能力太强，小 D 的跳跃长度有个下限 S，但没有上限。现在请你判断他是否能够完成他的目标。

## 输入格式
第一行输入两个整数 N,M,S，分别表示河的宽度，岩石的数量和跳跃长度的下限。

第二行输入 M 个整数，分别表示 M 个岩石的坐标 w_1,w_2,...,w_N。保证 {w_i} 为递增序列。

## 输出格式
如果小D可以完成他的目标，第一行输出 YES，第二行输出 M+2 个数，依次表示小D跳到的石头编号。特殊的，坐标为 0 的河岸编号为 0，坐标为 N 的河岸标号为 M+1 。如果有多种解法，允许输出任意一种。

如果小 D 不能完成他的目标，第一行输出 NO。

## 样例
### 样例1
**输入：**
```
6 1 3
3
```
**输出：**
```
YES
1 2 0
```

### 样例2
**输入：**
```
6 2 2
2 4
```
**输出：**
```
YES
2 3 1 0
```

### 样例3
**输入：**
```
5 2 3
2 3
```
**输出：**
```
NO
```

## 提示
对于全部数据，保证 1 ≤ N,S ≤ 10^5，0 ≤ M < N，1 ≤ w_i < N。

## 解题思路

### 问题分析
本题要求判断是否能按照特定规则跳过所有岩石，并给出跳跃路径。

### 核心思路
使用全排列或DFS搜索可能的跳跃路径。

### 算法流程
1. 生成所有可能的跳跃顺序
2. 检查每次跳跃的距离是否满足要求
3. 找到一条有效路径

### 复杂度分析
- 时间复杂度：O(M!)
- 空间复杂度：O(M)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s;
    cin >> n >> m >> s;
    
    vector<int> stones(m);
    for (int i = 0; i < m; i++) {
        cin >> stones[i];
    }
    
    stones.insert(stones.begin(), 0);
    stones.push_back(n);
    
    int total = m + 2;
    vector<int> order(total);
    for (int i = 0; i < total; i++) {
        order[i] = i;
    }
    
    bool found = false;
    vector<int> result;
    
    do {
        bool valid = true;
        for (int i = 1; i < total; i++) {
            int dist = abs(stones[order[i]] - stones[order[i-1]]);
            if (dist < s) {
                valid = false;
                break;
            }
        }
        if (valid) {
            found = true;
            result = order;
            break;
        }
    } while (next_permutation(order.begin() + 1, order.end() - 1));
    
    if (found) {
        cout << "YES" << endl;
        for (int i = 0; i < total; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
```