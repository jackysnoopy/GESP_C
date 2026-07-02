#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

// 求最大公约数
int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

const int MAXN = 1000001;
bool used[MAXN]; // 标记某个数是否属于某个毕达哥拉斯三元组

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        memset(used, 0, sizeof(used));
        int cntPrimitive = 0; // 本原三元组计数
        int maxM = (int)sqrt((double)N);

        // 枚举欧几里得公式中的 m, n
        for (int m = 2; m <= maxM; m++) {
            for (int n = 1; n < m; n++) {
                // m - n 必须为奇数，且 m, n 互质，才能生成本原三元组
                if ((m - n) % 2 == 0) continue;
                if (gcd(m, n) != 1) continue;

                int a = m * m - n * n;
                int b = 2 * m * n;
                int c = m * m + n * n;
                if (c > N) continue;

                cntPrimitive++;
                // 标记该本原三元组及其所有倍数（非本原三元组）
                for (int k = 1; k * c <= N; k++) {
                    used[k * a] = true;
                    used[k * b] = true;
                    used[k * c] = true;
                }
            }
        }

        // 统计不属于任何三元组的数字个数
        int cntNoPart = 0;
        for (int i = 1; i <= N; i++) {
            if (!used[i]) cntNoPart++;
        }

        printf("%d %d\n", cntPrimitive, cntNoPart);
    }
    return 0;
}
