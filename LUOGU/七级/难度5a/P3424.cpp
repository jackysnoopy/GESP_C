#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000005;
int a[MAXN], b[MAXN], c[MAXN];

void add(int n1, int n2) {
    int n = max(n1, n2);
    
    // 先将两个数相加
    for (int i = 1; i <= n; i++) {
        c[i] = a[i] + b[i];
    }
    
    // 从高位向低位处理进位
    for (int i = n; i >= 2; i--) {
        if (c[i] >= 2) {
            if (c[i] == 2) {
                c[i] = 0;
                c[i - 1] += 1;
                c[i - 2] += 1;
            } else {
                c[i] -= 2;
                c[i - 1] += 2;
                c[i - 2] += 2;
            }
        }
    }
    
    // 处理最低位
    if (c[1] >= 2) {
        c[1] -= 2;
        c[2] += 1;
    }
    if (c[0] >= 2) {
        c[0] -= 2;
        c[1] += 1;
        c[2] += 1;
    }
    
    // 消除连续的1
    for (int i = 2; i < MAXN; i++) {
        if (c[i] && c[i - 1]) {
            int t = min(c[i], c[i - 1]);
            c[i] -= t;
            c[i - 1] -= t;
            c[i + 1] += t;
        }
    }
    
    // 进一步处理
    for (int i = 1; i < MAXN - 1; i++) {
        if (c[i] >= 2) {
            c[i] -= 2;
            c[i - 1] += 1;
            c[i + 1] += 1;
        }
    }
}

int main() {
    int n1, n2;
    
    scanf("%d", &n1);
    for (int i = 1; i <= n1; i++) scanf("%d", &a[i]);
    
    scanf("%d", &n2);
    for (int i = 1; i <= n2; i++) scanf("%d", &b[i]);
    
    int n = max(n1, n2) + 2;
    add(n1, n2);
    
    // 找到最高位
    while (n > 1 && c[n] == 0) n--;
    
    printf("%d", n);
    for (int i = 1; i <= n; i++) {
        printf(" %d", c[i]);
    }
    printf("\n");
    
    return 0;
}
