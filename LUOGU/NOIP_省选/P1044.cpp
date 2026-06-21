#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    long long f[20] = {0};
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++)
            f[i] += f[j-1] * f[i-j];
    cout << f[n] << "\n";
    return 0;
}