#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 500005;
int N, M;
int l[MAXN], r[MAXN], c[MAXN];
int b[MAXN];
vector<int> pos[MAXN];

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", &l[i], &r[i], &c[i]);
    }
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &b[i]);
    }
    
    // 检查是否有解
    // 每个格子最后的颜色必须是某个操作的颜色
    for (int i = 1; i <= N; i++) {
        if (b[i] == 0) continue;
        
        bool found = false;
        for (int j = 1; j <= M; j++) {
            if (l[j] <= i && i <= r[j] && c[j] == b[i]) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            printf("NE\n");
            return 0;
        }
    }
    
    // 构造涂色顺序
    vector<int> order;
    vector<bool> used(M + 1, false);
    
    // 简单构造：按颜色分组
    map<int, vector<int>> color_ops;
    for (int i = 1; i <= M; i++) {
        color_ops[c[i]].push_back(i);
    }
    
    for (auto& p : color_ops) {
        for (int op : p.second) {
            order.push_back(op);
        }
    }
    
    printf("DA\n");
    for (int i = 0; i < M; i++) {
        printf("%d%c", order[i], i == M - 1 ? '\n' : ' ');
    }
    
    return 0;
}