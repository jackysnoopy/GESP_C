#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n + 1, 0));
    vector<vector<double>> p(n + 1, vector<double>(n));
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < n; ++j) cin >> p[i][j];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = 2.0 * (p[i + 1][j] - p[i][j]);
            a[i][n] += p[i + 1][j] * p[i + 1][j] - p[i][j] * p[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        int mx = i;
        for (int j = i + 1; j < n; ++j)
            if (fabs(a[j][i]) > fabs(a[mx][i])) mx = j;
        swap(a[i], a[mx]);
        double piv = a[i][i];
        for (int j = i; j <= n; ++j) a[i][j] /= piv;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            double f = a[j][i];
            for (int k = i; k <= n; ++k) a[j][k] -= f * a[i][k];
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        printf("%.3f", a[i][n]);
    }
    cout << '\n';
    return 0;
}
