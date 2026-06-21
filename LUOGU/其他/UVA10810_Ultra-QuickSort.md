# Ultra-QuickSort

## 题目描述
[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1751

[PDF](https://uva.onlinejudge.org/external/108/p10810.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/751b373c4650fd9cb6ed8962c612343e8c3faf34.png)

## 输入格式
![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/bbac08e36c21bfb711cef255cbd33a4aba31f921.png)

## 输出格式
![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/07aa3a0e09920ab537e7e75fdd2f783aadf38833.png)

## 样例
### 样例 1
```
5
9
1
0
5
4
3
1
2
3
0
```
```
6
0
```

## 解题思路

### 问题分析
求冒泡排序的交换次数，即数组的逆序对个数。

### 核心思路
用归并排序或树状数组统计逆序对个数。

### 算法流程
1. 读入 N 和序列
2. 用归并排序统计逆序对
3. 输出结果

### 复杂度分析
- 时间复杂度：O(N log N)
- 空间复杂度：O(N)

## 参考代码
```cpp
#include <iostream>
#include <vector>
using namespace std;

long long merge_sort(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    long long ans = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    
    vector<int> tmp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else {
            tmp.push_back(a[j++]);
            ans += mid - i + 1;
        }
    }
    while (i <= mid) tmp.push_back(a[i++]);
    while (j <= r) tmp.push_back(a[j++]);
    for (int k = 0; k < (int)tmp.size(); k++)
        a[l + k] = tmp[k];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;
        vector<int> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];
        cout << merge_sort(a, 0, N - 1) << "\n";
    }
    
    return 0;
}
```
