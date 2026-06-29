#include <cstdio>
#include <algorithm>
using namespace std;
long long a[3][3];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%lld", &a[i][j]);
            }
        }
        long long out1 = a[0][1] + a[1][1] + a[2][1];
        long long out2 = a[0][2] + a[1][2] + a[2][2];
        long long in1 = a[1][0] + a[1][1] + a[1][2];
        long long in2 = a[2][0] + a[2][1] + a[2][2];
        long long ans = min(out1, in2) + min(out2, in1);
        printf("%lld\n", ans);
    }
    return 0;
}