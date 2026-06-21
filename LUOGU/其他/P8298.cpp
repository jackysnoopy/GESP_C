#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
struct Meal { long long a, b; };
bool cmpB(const Meal& x, const Meal& y) { return x.b < y.b; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Meal m[500001];
    for (int i = 0; i < n; i++) cin >> m[i].a >> m[i].b;
    sort(m, m + n, cmpB);
    long long minA = m[0].a;
    long long sumB = m[0].b;
    printf("%lld\n", minA);
    for (int i = 1; i < n; i++) {
        minA = min(minA, m[i].a);
        sumB += m[i].b;
        printf("%lld\n", minA + sumB - m[i].b);
    }
    return 0;
}
