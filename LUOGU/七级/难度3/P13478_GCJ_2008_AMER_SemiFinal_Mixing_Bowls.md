# [GCJ 2008 AMER SemiFinal] Mixing Bowls

## 题目描述

You are following a recipe to create your lunch.

The recipe is a mixture made by combining ingredients together in a bowl. Each ingredient will be either:

- Another mixture which you must make first in a separate bowl; or
- A basic ingredient you already have in your kitchen, which can be added directly.

To make a mixture, you need to have all its ingredients ready, take an empty bowl and mix the ingredients in it. It is not possible to make mixtures by adding ingredients to an already-existing mixture in a bowl.

For example, if you want to make CAKE (a mixture) out of CAKEMIX (a mixture) and lies (a basic ingredient), then you must first make CAKEMIX in its own bowl, then add the CAKEMIX and lies to a second bowl to make the CAKE.

Once you have used a mixture as an ingredient and emptied the bowl it was prepared in, you can re-use that bowl for another mixture. So the number of bowls you need to prepare the recipe will depend on the order in which you decide to make mixtures.

Determine the minimum number of bowls you will need.

## 输入格式

The first line will contain an integer $C$, the number of test cases in the input file.

For each test case, there will be:

- One line containing an integer $N$, the number of mixtures in the test case.
- $N$ lines, one for each mixture, containing:
    - One string giving the mixture name;
    - An integer $M$, the number of ingredients in this mixture;
    - $M$ strings, giving the names of each of the ingredients of this mixture.

The tokens on one line will be separated by single spaces.

The first mixture in a test case is the recipe you are making.

The names of mixtures are strings of between $1$ and $20$ UPPERCASE letters.

The names of basic ingredients are strings of between $1$ and $20$ lowercase letters.

Each mixture is used in exactly one other mixture, except for the recipe, which is not used in any other mixture. Each ingredient will appear at most once in the ingredient list for a mixture. No mixture will (directly or indirectly) require itself as an ingredient.

## 输出格式

For each test case, output one line containing "Case #$X$: $Y$" where $X$ is the number of the test case, starting from $1$, and $Y$ is the minimum number of mixing bowls required.

## 样例

### 样例输入 1
```
2
3
SOUP 3 STOCK salt water
STOCK 2 chicken VEGETABLES
VEGETABLES 2 celery onions
5
MILKSHAKE 4 milk icecream FLAVOR FRUIT
FRUIT 2 banana berries
FLAVOR 2 SPICES CHOCOLATE
SPICES 2 nutmeg cinnamon
CHOCOLATE 2 cocoa syrup
```

### 样例输出 1
```
Case #1: 2
Case #2: 3
```

## 提示

**Sample Explanation**

In the first case, to satisfy your craving for SOUP, you follow these steps:

1. Make VEGETABLES by mixing celery and onions in a bowl.
2. Make STOCK in a second bowl by mixing chicken and VEGETABLES from the first bowl. The first bowl becomes empty.
3. Make SOUP in the first bowl by mixing STOCK, salt and water.

In the second case, you have a choice of whether to make FLAVOR or FRUIT first before mixing them with milk and icecream to make MILKSHAKE.

If we make FRUIT first, we use four bowls:

1. Make FRUIT in a bowl by mixing banana and berries.
2. Make SPICES in a second bowl by mixing nutmeg and cinnamon, and CHOCOLATE in a third bowl by mixing cocoa and syrup. (In either order)
3. Make FLAVOR in a fourth bowl by mixing SPICES and CHOCOLATE.
4. Make MILKSHAKE in the second or third bowl by mixing FRUIT, FLAVOR, milk and icecream.

However if we make FRUIT after FLAVOR, we use three bowls:

1. Make SPICES in a bowl by mixing nutmeg and cinnamon, and CHOCOLATE in a second bowl by mixing cocoa and syrup. (In either order)
2. Make FLAVOR in a third bowl by mixing SPICES and CHOCOLATE.
3. Make FRUIT in the first bowl by mixing banana and berries.
4. Make MILKSHAKE in the second bowl by mixing FRUIT, FLAVOR, milk and icecream.

**Limits**

- $1 \leq C \leq 10$
- $2 \leq M \leq 10$

**Small dataset (5 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 10$

**Large dataset (9 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 1000$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
map<string, vector<string>> ch;
map<string, bool> isMix;
int compute(const string& name) {
    if (!isMix.count(name) || !isMix[name]) return 0;
    vector<int> cb;
    for (const string& ing : ch[name])
        if (isMix.count(ing) && isMix[ing]) cb.push_back(compute(ing));
    sort(cb.begin(), cb.end(), greater<int>());
    int m = cb.size();
    int result = m + 1;
    for (int i = 0; i < m; i++) result = max(result, i + cb[i]);
    return result;
}
int main() {
    int C;
    cin >> C;
    for (int tc = 1; tc <= C; tc++) {
        int N;
        cin >> N;
        ch.clear(); isMix.clear();
        vector<string> names;
        for (int i = 0; i < N; i++) {
            string name; int M;
            cin >> name >> M;
            isMix[name] = true;
            names.push_back(name);
            for (int j = 0; j < M; j++) { string ing; cin >> ing; ch[name].push_back(ing); }
        }
        cout << "Case #" << tc << ": " << compute(names[0]) << "\n";
    }
    return 0;
}
```

## 解题思路

### 问题分析
题目要求计算制作一个配方所需的最少碗数。配方由多个混合物组成，每个混合物可能需要先制作其他混合物。每个混合物需要一个空碗，但使用完后可以重复利用。

### 核心思路
这是一个树形结构问题。对于每个混合物，递归计算其子混合物所需的碗数。将子混合物按所需碗数从大到小排序，然后贪心地安排制作顺序，使得并行制作的混合物数量最多。

### 算法流程
1. 读入混合物的依赖关系，构建树形结构
2. 对于每个混合物，递归计算其子混合物所需的碗数
3. 将子混合物按所需碗数降序排序
4. 使用公式 $\max(m+1, \max_{i}(i + cb[i]))$ 计算当前混合物所需的碗数
5. 输出最终结果

### 复杂度分析
- 时间复杂度：$O(N \log N)$，排序操作
- 空间复杂度：$O(N)$，存储混合物依赖关系

## 解题思路

### 问题分析
给定一组混合物的依赖关系，每种混合物由基本原料或其他混合物组成。制作混合物需要先准备好所有子混合物，然后用一个空碗混合。混合物被使用后碗可以回收。目标是求制作最终食谱所需的最少碗数。

### 核心思路
将混合物依赖关系建模为一棵树（或 DAG），对每个混合物递归计算其子混合物所需的碗数。核心贪心策略：将子混合物按所需碗数降序排列，然后依次分配碗。若第 $i$ 个子混合物需要 $cb[i]$ 个碗，则至少需要 $i + cb[i]$ 个碗（因为前 $i$ 个子混合物占用了 $i$ 个碗作为并行，加上当前混合物本身需要 $1$ 个碗）。最终结果为 $\max(m+1, \max_i(i + cb[i]))$，其中 $m$ 是子混合物的数量。

### 算法流程
1. 读入混合物的依赖关系，用 map 存储每种混合物的成分列表
2. 从最终食谱（第一个混合物）开始递归调用 `compute` 函数
3. 对于每个混合物，递归计算其所有子混合物混合物成分所需的碗数
4. 将子混合物所需碗数按降序排序
5. 计算结果：基础值为 $m+1$（$m$ 个子混合物 + 当前碗），同时检查是否需要更多碗
6. 输出最终食谱的计算结果

### 复杂度分析
- 时间复杂度：$O(N \log N)$，每个混合物递归一次，排序子混合物结果需要 $O(m \log m)$
- 空间复杂度：$O(N)$，存储依赖关系和递归栈

---
