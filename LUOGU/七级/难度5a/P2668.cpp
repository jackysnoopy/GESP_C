#include <bits/stdc++.h>
using namespace std;

int T, n;
int cnt[20];
int ans;

void dfs(int step) {
    if (step >= ans) return;
    
    // 计算剩余牌数
    int remain = 0;
    for (int i = 1; i <= 14; i++) remain += cnt[i];
    if (remain == 0) {
        ans = step;
        return;
    }
    
    // 火箭
    if (cnt[14] && cnt[15]) {
        cnt[14]--; cnt[15]--;
        dfs(step + 1);
        cnt[14]++; cnt[15]++;
    }
    
    // 炸弹
    for (int i = 1; i <= 13; i++) {
        if (cnt[i] == 4) {
            cnt[i] = 0;
            dfs(step + 1);
            cnt[i] = 4;
        }
    }
    
    // 三带一、三带二
    for (int i = 1; i <= 13; i++) {
        if (cnt[i] >= 3) {
            cnt[i] -= 3;
            // 三带一
            for (int j = 1; j <= 13; j++) {
                if (cnt[j] >= 1) {
                    cnt[j]--;
                    dfs(step + 1);
                    cnt[j]++;
                }
            }
            // 三带二
            for (int j = 1; j <= 13; j++) {
                if (cnt[j] >= 2) {
                    cnt[j] -= 2;
                    dfs(step + 1);
                    cnt[j] += 2;
                }
            }
            // 不带
            dfs(step + 1);
            cnt[i] += 3;
        }
    }
    
    // 顺子（至少5张）
    for (int len = 5; len <= 12; len++) {
        for (int i = 1; i + len - 1 <= 13; i++) {
            bool ok = true;
            for (int j = i; j < i + len; j++) {
                if (cnt[j] < 1) { ok = false; break; }
            }
            if (ok) {
                for (int j = i; j < i + len; j++) cnt[j]--;
                dfs(step + 1);
                for (int j = i; j < i + len; j++) cnt[j]++;
            }
        }
    }
    
    // 连对（至少3对）
    for (int len = 3; len <= 10; len++) {
        for (int i = 1; i + len - 1 <= 13; i++) {
            bool ok = true;
            for (int j = i; j < i + len; j++) {
                if (cnt[j] < 2) { ok = false; break; }
            }
            if (ok) {
                for (int j = i; j < i + len; j++) cnt[j] -= 2;
                dfs(step + 1);
                for (int j = i; j < i + len; j++) cnt[j] += 2;
            }
        }
    }
    
    // 飞机（至少2个三张连续）
    for (int len = 2; len <= 6; len++) {
        for (int i = 1; i + len - 1 <= 13; i++) {
            bool ok = true;
            for (int j = i; j < i + len; j++) {
                if (cnt[j] < 3) { ok = false; break; }
            }
            if (ok) {
                for (int j = i; j < i + len; j++) cnt[j] -= 3;
                // 飞机不带翅膀
                dfs(step + 1);
                // 飞机带单牌
                vector<int> singles;
                for (int j = 1; j <= 15; j++) {
                    if (cnt[j] >= 1) singles.push_back(j);
                }
                if (singles.size() >= len) {
                    // 枚举所有可能的单牌组合
                    for (int mask = 0; mask < (1 << (int)singles.size()); mask++) {
                        if (__builtin_popcount(mask) == len) {
                            for (int j = 0; j < (int)singles.size(); j++) {
                                if (mask & (1 << j)) cnt[singles[j]]--;
                            }
                            dfs(step + 1);
                            for (int j = 0; j < (int)singles.size(); j++) {
                                if (mask & (1 << j)) cnt[singles[j]]++;
                            }
                        }
                    }
                }
                // 飞机带对子
                vector<int> pairs;
                for (int j = 1; j <= 13; j++) {
                    if (cnt[j] >= 2) pairs.push_back(j);
                }
                if (pairs.size() >= len) {
                    for (int mask = 0; mask < (1 << (int)pairs.size()); mask++) {
                        if (__builtin_popcount(mask) == len) {
                            for (int j = 0; j < (int)pairs.size(); j++) {
                                if (mask & (1 << j)) cnt[pairs[j]] -= 2;
                            }
                            dfs(step + 1);
                            for (int j = 0; j < (int)pairs.size(); j++) {
                                if (mask & (1 << j)) cnt[pairs[j]] += 2;
                            }
                        }
                    }
                }
                for (int j = i; j < i + len; j++) cnt[j] += 3;
            }
        }
    }
    
    // 四带二
    for (int i = 1; i <= 13; i++) {
        if (cnt[i] == 4) {
            cnt[i] = 0;
            // 四带两单
            for (int j = 1; j <= 15; j++) {
                if (cnt[j] >= 1) {
                    cnt[j]--;
                    for (int k = j; k <= 15; k++) {
                        if (cnt[k] >= 1) {
                            cnt[k]--;
                            dfs(step + 1);
                            cnt[k]++;
                        }
                    }
                    cnt[j]++;
                }
            }
            // 四带两对
            for (int j = 1; j <= 13; j++) {
                if (cnt[j] >= 2) {
                    cnt[j] -= 2;
                    for (int k = j; k <= 13; k++) {
                        if (cnt[k] >= 2) {
                            cnt[k] -= 2;
                            dfs(step + 1);
                            cnt[k] += 2;
                        }
                    }
                    cnt[j] += 2;
                }
            }
            cnt[i] = 4;
        }
    }
    
    // 单张、对子
    for (int i = 1; i <= 15; i++) {
        if (cnt[i] >= 2) {
            cnt[i] -= 2;
            dfs(step + 1);
            cnt[i] += 2;
        }
        if (cnt[i] >= 1) {
            cnt[i]--;
            dfs(step + 1);
            cnt[i]++;
        }
    }
}

int main() {
    scanf("%d%d", &T, &n);
    
    while (T--) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a == 0) cnt[b == 1 ? 14 : 15]++;
            else cnt[a]++;
        }
        
        ans = n;
        dfs(0);
        printf("%d\n", ans);
    }
    
    return 0;
}
