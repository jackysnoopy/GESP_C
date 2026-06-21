#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end(), greater<long long>());
    long long sum = 0;
    double ans = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        double cur = (double)(sum * sum) / (i + 1);
        if (cur > ans) ans = cur;
    }
    printf("%.10f\n", ans);
    return 0;
}
