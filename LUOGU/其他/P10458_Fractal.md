# Fractal

## 题目描述
A fractal is an object or quantity that displays self-similarity, in a somewhat technical sense, on all scales. The object need not exhibit exactly the same structure at all scales, but the same "type" of structures must appear on all scales.

A box fractal is defined as below :

-  A box fractal of degree $1$ is simply X
-  A box fractal of degree $2$ is
```
X X
 X
X X
```
- If using $B(n - 1)$ to represent the box fractal of degree $n - 1$, then a box fractal of degree $n$ is defined recursively as following
```
B(n - 1) B(n - 1)
     B(n - 1)
B(n - 1) B(n - 1)
```
Your task is to draw a box fractal of degree $n$.

## 输入格式
The input consists of several test cases. Each line of the input contains a positive integer $n$ which is no greater than $7$. The last line of input is a negative integer $-1$ indicating the end of input.

## 输出格式
For each test case, output the box fractal using the 'X' notation. Please notice that 'X' is an uppercase letter. Print a line with only a single dash after each test case.

## 样例
### 样例 1
```
1
2
3 
4 
-1
```
```
X
-
X X
 X 
X X
-
X X   X X
 X     X 
X X   X X
   X X   
    X    
   X X   
X X   X X
 X     X 
X X   X X
-
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
   X X               X X   
    X                 X    
   X X               X X   
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
         X X   X X         
          X     X          
         X X   X X         
            X X            
             X             
            X X            
         X X   X X         
          X     X          
         X X   X X         
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
   X X               X X   
    X                 X    
   X X               X X   
X X   X X         X X   X X
 X     X           X     X 
X X   X X         X X   X X
-
```

## 解题思路
### 问题分析
分形递归输出。给定度数 n，输出分形图形。每个分形由更小规模的分形按 3×3 网格排列组成。

### 核心思路
递归构建。n=1 时为一个格子；n>1 时在 3^(n-1)×3^(n-1) 网格中按位置填充。

### 算法流程
1. 读入 n
2. 计算 size = 3^(n-1)
3. 递归填充画布
4. 输出

### 复杂度分析
- 时间复杂度：O(3^(2n))
- 空间复杂度：O(3^(2n))

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<string> canvas;

void draw(int n, int x, int y) {
    if (n == 1) {
        canvas[x][y] = 'X';
        return;
    }
    int sz = pow(3, n - 2);
    draw(n - 1, x, y);
    draw(n - 1, x, y + 2 * sz);
    draw(n - 1, x + sz, y + sz);
    draw(n - 1, x + 2 * sz, y);
    draw(n - 1, x + 2 * sz, y + 2 * sz);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n;
        cin >> n;
        if (n == -1) break;
        
        int sz = 1;
        for (int i = 1; i < n; i++) sz *= 3;
        
        canvas.assign(sz, string(sz, ' '));
        draw(n, 0, 0);
        
        for (const auto& row : canvas)
            cout << row << "\n";
        cout << "-\n";
    }
    return 0;
}
```
