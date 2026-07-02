# [BalticOI 2016] 迷宫 (Day2)

## 题目描述
构造迷宫，有地板(.),墙壁(#),基地(x),金币(o)。从基地出发收集金币再返回。给定n,m,k，构造迷宫使答案为k。

## 输入格式
第一行t，接下来t行每行n m k。

## 输出格式
t个迷宫，空行分隔。

## 样例
输入：
```
2
3 3 1
4 7 2
```
输出：
```
###
#.x
#o#

.o.####
.#..x.#
...##.#
###o...
```

## 解题思路

### 问题分析
- 构造题
- 可以用简单的构造方法

### 核心思路
- 在基地旁边放金币
- 用墙壁隔开

### 复杂度分析
- 时间复杂度：O(n*m)
- 空间复杂度：O(n*m)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        
        vector<string> maze(n, string(m, '.'));
        
        maze[0][0] = 'x';
        
        int placed = 0;
        for (int i = 0; i < n && placed < k; i++) {
            for (int j = 0; j < m && placed < k; j++) {
                if (i == 0 && j == 0) continue;
                if (placed < k) {
                    maze[i][j] = 'o';
                    placed++;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            cout << maze[i] << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}
```
