#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long n, a, b, c, d, e;
        cin >> n >> a >> b >> c >> d >> e;
        long long minScore = 0, maxScore = 0;
        if (d > e) {
            maxScore = d * a + (n - d) * c;
            minScore = d * a + (n - d) * c;
        } else if (d < e) {
            maxScore = e * a + (n - e) * c;
            minScore = e * a + (n - e) * c;
        } else {
            maxScore = n * c;
            minScore = n * c;
        }
        cout << maxScore << " " << minScore << "\n";
    }
    return 0;
}
