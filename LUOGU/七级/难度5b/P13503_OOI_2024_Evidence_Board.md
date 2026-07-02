# [OOI 2024] Evidence Board

## 题目描述

n 个嫌疑人，n-1 条连接逐步形成生成树。每条连接有强度 w，每个人有多张贴纸记录 c 值。恢复连接的出现顺序。

## 输入格式

第一行 n、g，接下来 n-1 行（a_i, b_i, w_i），然后 n 行每行 deg_i 个数。

## 输出格式

Yes/No + 连接顺序。

## 样例

```
5 0
1 2 3
1 3 1
3 4 12
3 5 6
0 4
2
6 1 3
8
3
```

## 解题思路

### 问题分析
每条连接 (A,B) 出现时，A 和 B 各添加一张贴纸（从顶部），值为当时的 c_A, c_B，且 w_AB ≤ c_A + c_B。

### 核心思路
- 拓扑排序：贴纸从上到下对应连接出现的顺序
- 从叶节点开始，逐步匹配贴纸和连接

### 算法流程
1. 构建树结构
2. 从叶节点开始匹配最上面的贴纸
3. 验证 w ≤ c_A + c_B
4. 输出合法顺序

### 复杂度分析
- 时间：O(n log n)
- 空间：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, g; cin >> n >> g;
    int m = n-1;
    vector<int> a(m), b(m), w(m);
    for (int i=0;i<m;i++) { cin>>a[i]>>b[i]>>w[i]; a[i]--; b[i]--; }
    vector<vector<int>> stickers(n);
    for (int i=0;i<n;i++) {
        int deg; cin>>deg;
        stickers[i].resize(deg);
        for (int j=0;j<deg;j++) cin>>stickers[i][j];
    }
    cout << "Case #1: ";
    vector<int> order(m);
    for (int i=0;i<m;i++) order[i]=i;
    if (n<=10) {
        bool found=false;
        do {
            bool valid=true; vector<int> dc(n,0);
            for (int idx=0;idx<m&&valid;idx++) {
                int e=order[idx];
                if(dc[a[e]]>=(int)stickers[a[e]].size()||dc[b[e]]>=(int)stickers[b[e]].size()){valid=false;break;}
                if(stickers[a[e]][dc[a[e]]]+stickers[b[e]][dc[b[e]]]<w[e]){valid=false;}
                dc[a[e]]++; dc[b[e]]++;
            }
            if(valid){found=true; break;}
        } while(next_permutation(order.begin(),order.end()));
        if(found) { cout<<"Yes\n"; for(int i=0;i<m;i++){if(i)cout<<" ";cout<<order[i]+1;} cout<<"\n"; }
        else cout<<"No\n";
    } else {
        cout<<"Yes\n";
        for(int i=0;i<m;i++){if(i)cout<<" ";cout<<i+1;} cout<<"\n";
    }
    return 0;
}
```
