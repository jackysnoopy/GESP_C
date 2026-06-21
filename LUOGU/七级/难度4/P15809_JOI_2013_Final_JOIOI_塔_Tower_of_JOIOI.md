# [JOI 2013 Final] JOIOI 塔 / Tower of JOIOI

## 题目描述

JOIOI の塔は，1 人で遊ぶ円盤を使ったゲームである．

このゲームは，**J**, **O**, **I** のいずれかの文字が書かれたいくつかの円盤を用いて行う．円盤は直径が互いに異なり，ゲーム開始時にはこれらの円盤は直径の大きいものから順に下から上に向かって積まれている．あなたは，これらの円盤を用いて，出来るだけ多くのミニ JOIOI の塔を作りたい．ミニ JOIOI の塔とは 3 枚の円盤からなり，円盤の直径が小さいものから順に読んで **JOI** もしくは **IOI** と読めるものである．ただし，同じ円盤を 2 度以上使うことはできない．

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/uqedfmzi.png)

図: **JOIOII** からはミニ JOIOI の塔が 2 つ作れる
:::

### 課題

用意された円盤に書かれた文字がそれぞれ円盤の直径が小さいものから順に長さ $N$ の文字列 $S$ として与えられる．これらの円盤を使って作ることのできるミニ JOIOI の塔の個数の最大値を求めるプログラムを作成せよ．

## 输入格式

標準入力から以下のデータを読み込め．

- 1 行目には整数 $N$ が書かれている．$N$ は文字列 $S$ の長さを表す．
- 2 行目には文字列 $S$ が書かれている．

## 输出格式

標準出力に，作ることのできるミニ JOIOI の塔の数の最大値を表す整数を 1 行で出力せよ．

## 样例

### 样例输入 1
```
6
JOIIOI
```

### 样例输出 1
```
2
```

### 样例输入 2
```
5
JOIOI
```

### 样例输出 2
```
1
```

### 样例输入 3
```
6
JOIOII
```

### 样例输出 3
```
2
```

### 样例输入 4
```
15
JJOIIOOJOJIOIIO
```

### 样例输出 4
```
4
```

## 提示

### 入出力例

1. JOIIOI は JOI および IOI をそれぞれ 1 つずつ部分列として含んでおり，作ることのできるミニ JOIOI の塔は 2 つである．
2. 部分列として JOI および IOI を含んでいるが，文字を 2 度以上使うことはできないため同時に取り出すことはできない．
3. この入出力例は問題文中の例に対応している．

### 制限

$1 \leq N \leq 1\,000\,000$　文字列 $S$ の長さ

### 採点基準

採点用データのうち，配点の 10% 分については，$N \leq 15$ を満たす．  
採点用データのうち，配点の 30% 分については，$N \leq 50$ を満たす．  
採点用データのうち，配点の 50% 分については，$N \leq 3000$ を満たす．

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S;
    cin >> N >> S;

    int j_count = 0, o_count = 0, i_count = 0;
    int ans = 0;

    for (char c : S) {
        if (c == 'J') j_count++;
        else if (c == 'O') o_count++;
        else i_count++;
    }

    int joi = min({j_count, o_count, i_count});
    int ioi = min({o_count / 2, i_count});

    cout << joi + ioi << "\n";
    return 0;
}
```
