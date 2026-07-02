#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        vector<int> perm(n + 1);
        for (int i = 1; i <= n; i++) cin >> perm[i];

        string text;
        cin >> text;

        // 应用置换一次得到密文
        string encrypted(n, ' ');
        for (int i = 0; i < n; i++) {
            encrypted[perm[i + 1] - 1] = text[i];
        }

        // 求置换循环节长度的LCM（解密需要的次数）
        vector<bool> visited(n + 1, false);
        int lcmResult = 1;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                int cycleLen = 0;
                int j = i;
                while (!visited[j]) {
                    visited[j] = true;
                    j = perm[j];
                    cycleLen++;
                }
                lcmResult = lcmResult / gcd(lcmResult, cycleLen) * cycleLen;
            }
        }

        cout << encrypted << "\n" << lcmResult << "\n\n";
    }
    return 0;
}
