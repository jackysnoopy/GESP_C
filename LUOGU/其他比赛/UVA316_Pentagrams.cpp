#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n) {
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        for (int m = l + 1; m < n; m++) {
                            ans++;
                        }
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
