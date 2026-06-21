# Cinema

## 题目描述
Moscow is hosting a major international conference, which is attended by $ n $ scientists from different countries. Each of the scientists knows exactly one language. For convenience, we enumerate all languages of the world with integers from $ 1 $ to $ 10^{9} $ .

In the evening after the conference, all $ n $ scientists decided to go to the cinema. There are $ m $ movies in the cinema they came to. Each of the movies is characterized by two distinct numbers — the index of audio language and the index of subtitles language. The scientist, who came to the movie, will be very pleased if he knows the audio language of the movie, will be almost satisfied if he knows the language of subtitles and will be not satisfied if he does not know neither one nor the other (note that the audio language and the subtitles language for each movie are always different).

Scientists decided to go together to the same movie. You have to help them choose the movie, such that the number of very pleased scientists is maximum possible. If there are several such movies, select among them one that will maximize the number of almost satisfied scientists.

## 输入格式
The first line of the input contains a positive integer $ n $ ( $ 1<=n<=200000 $ ) — the number of scientists.

The second line contains $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ), where $ a_{i} $ is the index of a language, which the $ i $ -th scientist knows.

The third line contains a positive integer $ m $ ( $ 1<=m<=200000 $ ) — the number of movies in the cinema.

The fourth line contains $ m $ positive integers $ b_{1},b_{2},...,b_{m} $ ( $ 1<=b_{j}<=10^{9} $ ), where $ b_{j} $ is the index of the audio language of the $ j $ -th movie.

The fifth line contains $ m $ positive integers $ c_{1},c_{2},...,c_{m} $ ( $ 1<=c_{j}<=10^{9} $ ), where $ c_{j} $ is the index of subtitles language of the $ j $ -th movie.

It is guaranteed that audio languages and subtitles language are different for each movie, that is $ b_{j}≠c_{j} $ .

## 输出格式
Print the single integer — the index of a movie to which scientists should go. After viewing this movie the number of very pleased scientists should be maximum possible. If in the cinema there are several such movies, you need to choose among them one, after viewing which there will be the maximum possible number of almost satisfied scientists.

If there are several possible answers print any of them.

## 样例
### 样例 1
```
3
2 3 2
2
3 2
2 3

```
```
2
```

### 样例 2
```
6
6 3 1 1 3 7
5
1 2 3 4 5
2 3 4 5 1

```
```
1
```

## 提示
In the first sample, scientists must go to the movie with the index $ 2 $ , as in such case the $ 1 $ -th and the $ 3 $ -rd scientists will be very pleased and the $ 2 $ -nd scientist will be almost satisfied.

In the second test case scientists can go either to the movie with the index $ 1 $ or the index $ 3 $ . After viewing any of these movies exactly two scientists will be very pleased and all the others will be not satisfied.

## 解题思路

### 问题分析
n 个科学家各会一种语言。有 m 部电影，各有语音语言和字幕语言。选一部电影使很高兴（听得懂语音）的人最多，其次比较满意（看得懂字幕）的人最多。

### 核心思路
用 map 统计每种语言的人数，然后遍历电影找最优解。

### 算法流程
1. 读入科学家语言，统计每种语言人数
2. 读入 m 部电影的语音和字幕语言
3. 遍历电影，计算很高兴和比较满意的人数
4. 按双关键字选择最优电影

### 复杂度分析
- 时间复杂度：O((n+m) log n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int lang;
        cin >> lang;
        cnt[lang]++;
    }
    
    int m;
    cin >> m;
    vector<int> audio(m), sub(m);
    for (int i = 0; i < m; i++) cin >> audio[i];
    for (int i = 0; i < m; i++) cin >> sub[i];
    
    int best_idx = 0, best_audio = -1, best_sub = -1;
    for (int i = 0; i < m; i++) {
        int a = cnt[audio[i]];
        int s = cnt[sub[i]];
        if (a > best_audio || (a == best_audio && s > best_sub)) {
            best_audio = a;
            best_sub = s;
            best_idx = i + 1;
        }
    }
    
    cout << best_idx << "\n";
    return 0;
}
```
