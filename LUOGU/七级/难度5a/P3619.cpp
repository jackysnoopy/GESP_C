#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int n;
long long T;
pair<int, int> tasks[MAXN]; // (t_i, b_i)

int main() {
    int Z;
    scanf("%d", &Z);
    
    while (Z--) {
        scanf("%d%lld", &n, &T);
        
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &tasks[i].first, &tasks[i].second);
        }
        
        // 按t_i排序
        sort(tasks, tasks + n);
        
        bool ok = true;
        long long time = T;
        
        for (int i = 0; i < n; i++) {
            if (time <= tasks[i].first) {
                ok = false;
                break;
            }
            time += tasks[i].second;
            if (time <= 0) {
                ok = false;
                break;
            }
        }
        
        printf("%s\n", ok ? "+1s" : "-1s");
    }
    
    return 0;
}
