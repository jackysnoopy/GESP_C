# P4442 [COCI 2017/2018 #3] Portal

## 题目描述
The protagonist of this task, Chell, must solve a new puzzle GLaDOS has come up with.

Chell is in a room whose layout that can be represented as a matrix of dimensions N rows and M columns. Each field can be one of the following:

- Obstructed field - there is a wall in it (denoted as ‘#’),
- The field where Chell is initially (denoted as ‘C’),
- The field where Chell must get to in order to solve the puzzle (denoted as ‘F’), or
- An empty field (denoted as ‘.’).

Chell is carrying a so-called portal gun, a gun with which you can create portals in the walls.

In each move, she can do one of the following:
- Move to an adjacent field using one move up, down, left or right (she cannot move to the field with a wall in it). This move lasts one unit of time.
- Create a portal in the wall by turning towards a wall, not necessarily an adjacent one, in the direction up, down, left or right and shooting. The portal will be created only on the side of the wall it was hit from. In each moment, **at most two portals can be active**​. If a new portal is being created in the moment when two portals are already active, the one that was created earlier will disappear. It is not possible to create a new portal at the position of another existing portal. This move lasts a negligible
amount of time, i.e. zero amounts of time.
- If she’s at a field that is adjacent to a wall and there’s a portal on her side of the wall, she can step into the portal and exit to a non-obstructed field with another portal. This move is possible if there are two active portals and lasts one unit of time.

Chell wants to know the minimal amount of time it takes for her to solve the puzzle, i.e. to reach the field denoted as ‘F’.

**Please note**: The room will always have walls on the sides, and letters ‘C’ and ‘F’ will appear only once in the matrix.

## 输入格式
The first line of input contains the positive integers N and M (4 ≤ N, M ≤ 500), the numbers from the task.

Each of the following N lines contains M characters that describe the layout of the room.

## 输出格式
You must output the minimal amount of time it takes to solve the puzzle, or “nemoguce” (without quotation marks, Croatian for impossible) if it is not possible to solve it.

## 样例
### 样例1
输入：
```
4 4
####
#.F#
#.C.#
####
```
输出：
```
2
```

### 样例2
输入：
```
6 8
########
#.##..F#
#.C.##..#
#..#...#
#.....##
########
```
输出：
```
4
```

### 样例3
输入：
```
4 5
#####
#.C#.#
###F#
#####
```
输出：
```
nemoguce
```

## 提示
In test cases worth 50% of total points, it will hold 4 ≤ N, M ≤ 15.

**Clarification​ ​of​ ​the​ ​second​ ​test​ ​case:**

The puzzle can be solved in 8 moves, illustrated in the pictures below.

In the first move, we turn towards the left wall, shoot and create a portal that appears on the wall in the $3^{rd}$ row and $1^{st}$ column (coordinates (3,1)) from the right side.

In the second move, we create a portal from the upper side of the wall at coordinates (6,2).

In the third move, we step into the portal at coordinates (3,1) and exit at coordinates (5,2) - a
non-obstructed field with the second portal.

In the fourth move, we turn right and create a portal from the left side of the wall at coordinates (5,7).
Since there are already two portals, the one at field (3,1) disappears.

In the fifth move, we step into the portal at coordinates (6,2) and exit at coordinates (5,6) with the
second portal.

In the sixth move, we create a new portal from the lower side of the wall at coordinates (1,6), making
the portal at coordinates (6,2) disappear.

In the seventh move, we step into the portal at coordinates (5,7) and exit at coordinates (2,6).
Finally, in the eighth move, we move one place to the right to end the game.

The portal creation in moves 1, 2, 4 and 6 lasts zero amounts of time, whereas the rest of the move
last one unit of time, so the total time needed to solve the puzzle is 4 units of time.

![](https://cdn.luogu.com.cn/upload/pic/17512.png)

## 解题思路

### 问题分析
这是一个网格图上的最短路径问题，状态包括当前位置和传送门状态。传送门可以创建在墙壁上，最多同时存在两个。使用传送门移动需要时间，但创建传送门不需要时间。

### 核心思路
使用BFS搜索，状态为 (x, y, p1, p2)，其中 (x, y) 是当前位置，p1 和 p2 是两个传送门的位置（如果存在）。由于传送门最多两个，且创建传送门不耗时，可以将状态简化为 (x, y, p1, p2)，其中 p1 和 p2 可能为空。

### 算法流程
1. 初始化BFS队列，起始状态为 (C的位置, 空, 空)，时间为0。
2. 对于每个状态，尝试三种操作：
   - 移动到相邻的空格子，时间+1。
   - 创建传送门：选择一个方向，找到最近的墙壁，在墙壁上创建传送门（如果已有两个，则替换最早的）。时间不变。
   - 使用传送门：如果当前位置相邻有传送门，且有两个传送门，则传送到另一个传送门的位置，时间+1。
3. 继续搜索直到到达终点 'F'，返回时间。
4. 如果无法到达，输出 "nemoguce"。

### 复杂度分析
- 时间复杂度：O(N*M*4*4)，因为传送门位置最多有4种可能（每个方向一个）。
- 空间复杂度：O(N*M*4*4)，用于存储状态。

## 参考代码
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 505;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

struct State {
    int x, y, p1x, p1y, p2x, p2y, dist;
    State(int x, int y, int p1x, int p1y, int p2x, int p2y, int dist)
        : x(x), y(y), p1x(p1x), p1y(p1y), p2x(p2x), p2y(p2y), dist(dist) {}
};

char grid[MAXN][MAXN];
bool visited[MAXN][MAXN][5][5];
int n, m;

int bfs(int sx, int sy) {
    queue<State> q;
    q.push(State(sx, sy, -1, -1, -1, -1, 0));
    visited[sx][sy][0][0] = true;
    
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        
        if (grid[cur.x][cur.y] == 'F') {
            return cur.dist;
        }
        
        // Move
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == '#') continue;
            if (!visited[nx][ny][cur.p1x][cur.p1y]) {
                visited[nx][ny][cur.p1x][cur.p1y] = true;
                q.push(State(nx, ny, cur.p1x, cur.p1y, cur.p2x, cur.p2y, cur.dist + 1));
            }
        }
        
        // Create portal
        if (cur.p1x == -1) {
            // No portals yet
            for (int i = 0; i < 4; i++) {
                int nx = cur.x + dx[i];
                int ny = cur.y + dy[i];
                while (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#') {
                    nx += dx[i];
                    ny += dy[i];
                }
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (!visited[cur.x][cur.y][nx][ny]) {
                    visited[cur.x][cur.y][nx][ny] = true;
                    q.push(State(cur.x, cur.y, nx, ny, -1, -1, cur.dist));
                }
            }
        } else if (cur.p2x == -1) {
            // One portal exists
            for (int i = 0; i < 4; i++) {
                int nx = cur.x + dx[i];
                int ny = cur.y + dy[i];
                while (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#') {
                    nx += dx[i];
                    ny += dy[i];
                }
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (!visited[cur.x][cur.y][cur.p1x][cur.p1y]) {
                    visited[cur.x][cur.y][cur.p1x][cur.p1y] = true;
                    q.push(State(cur.x, cur.y, cur.p1x, cur.p1y, nx, ny, cur.dist));
                }
            }
        }
        
        // Use portal
        if (cur.p1x != -1 && cur.p2x != -1) {
            // Two portals exist
            for (int i = 0; i < 4; i++) {
                int nx = cur.x + dx[i];
                int ny = cur.y + dy[i];
                if (nx == cur.p1x && ny == cur.p1y) {
                    if (!visited[cur.p2x][cur.p2y][cur.p1x][cur.p1y]) {
                        visited[cur.p2x][cur.p2y][cur.p1x][cur.p1y] = true;
                        q.push(State(cur.p2x, cur.p2y, cur.p1x, cur.p1y, cur.p2x, cur.p2y, cur.dist + 1));
                    }
                }
                if (nx == cur.p2x && ny == cur.p2y) {
                    if (!visited[cur.p1x][cur.p1y][cur.p1x][cur.p1y]) {
                        visited[cur.p1x][cur.p1y][cur.p1x][cur.p1y] = true;
                        q.push(State(cur.p1x, cur.p1y, cur.p1x, cur.p1y, cur.p2x, cur.p2y, cur.dist + 1));
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    cin >> n >> m;
    int sx, sy;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'C') {
                sx = i;
                sy = j;
            }
        }
    }
    memset(visited, false, sizeof(visited));
    int ans = bfs(sx, sy);
    if (ans == -1) {
        cout << "nemoguce" << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
```
