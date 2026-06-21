# [SWERC 2024] Temple Architecture

## 题目描述

You are excavating what remains of a very old Indian temple. The architecture of the temple is very curious: you found a line of $N$ towers of different heights (no two towers have the same height), all spaced by one meter (the radius of each tower is supposed to be negligible).

During the excavations, you find something which might explain this curious architecture: the tomb of the architect. You find the following epitaph on the tomb:

> O thou temple-builder,   
> To achieve perfection, visit each tower;   
> For each, compute the distance to the    closest tower that is taller¹;   
> Add every such distance.   
> If thou can follow this guidance,   
> Enlightened shalt thou be by this result,   
> And great in thy temple shall be the cult.   

¹The closest taller tower can be on the left or on the right. For the tallest tower, this distance is undefined and should not be considered in the final sum.

You wonder how to compute this sum, this “enlightenment score” of the temple.

You are given a positive integer $N$ corresponding to the number of towers, and an array $H$ of $N$ distinct non-negative integers corresponding to the heights of the towers. $H_0$ is the height of the leftmost tower, $H_1$ is the height of the tower to the right of $H_0$, and so on. Finally, $H_{N-1}$ is the height of the rightmost tower. Observe that the distance between any two towers, in meters, is the absolute value of the difference of their respective indices in the array $H$. Let $p$ denote the index of the tallest tower in $H$ and define, for every $i \neq p$,

$$
d(i) = \min \{ |i - j| : \text{for every } j \text{ such that } H_j > H_i \}.
$$

Note that $d(p)$ is not defined. The “enlightenment score” of the temple is then given by

$$
\sum_{i=0, i \neq p}^{N-1} d(i).
$$

## 输入格式

The first line contains the integer $N$. The second line contains the list of elements $H_0, \ldots, H_{N-1}$ of the array $H$ of heights, separated by spaces.

## 输出格式

The output should contain one line with the enlightenment score of the temple.

## 样例

### 样例输入 1
```
5
7 3 2 100 1
```

### 样例输出 1
```
6
```

### 样例输入 2
```
8
45 13 18 10 8 56 17 19
```

### 样例输出 2
```
13
```

## 提示

### Sample Explanation 1

- Distance of the 1st tower to the closest taller tower (4th tower): $3$
- Distance of the 2nd tower to the closest taller tower (1st tower): $1$
- Distance of the 3rd tower to the closest taller tower (2nd or 4th tower): $1$
- Distance of the 5th tower to the closest taller tower (4th tower): $1$

The tallest tower (the 4th) is not considered. Hence, $3+1+1+1=6$.

### Sample Explanation 2

- Distance of the 1st tower to the closest taller tower (6th tower): $5$
- Distance of the 2nd tower to the closest taller tower (1st or 3rd tower): $1$
- Distance of the 3rd tower to the closest taller tower (1st tower): $2$
- Distance of the 4th tower to the closest taller tower (3rd tower): $1$
- Distance of the 5th tower to the closest taller tower (4th or 6th tower): $1$
- Distance of the 7th tower to the closest taller tower (6th or 8th tower): $1$
- Distance of the 8th tower to the closest taller tower (6th tower): $2$

The tallest tower (the 6th) is not considered. Hence, $5+1+2+1+1+1+2=13$.

### Limits

- $2 \leq N \leq 200000$;
- $0 \leq H_i \leq 10^{18}$ for $i = 1, \ldots, N$；

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> heights(n);
    for (int i = 0; i < n; i++) cin >> heights[i];

    int maxH = *max_element(heights.begin(), heights.end());
    cout << maxH << "\n";
    return 0;
}
```
