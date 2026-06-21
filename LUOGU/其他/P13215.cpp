#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<int> m(N);
        for (int i = 0; i < N; i++) cin >> m[i];
        int y = 0; // method 1: sum of decreases
        for (int i = 1; i < N; i++) {
            if (m[i] < m[i - 1]) y += m[i - 1] - m[i];
        }
        int rate = 0; // method 2
        for (int i = 1; i < N; i++) {
            rate = max(rate, m[i - 1] - m[i]);
        }
        int z = 0;
        for (int i = 0; i < N - 1; i++) {
            z += min(m[i], rate);
        }
        cout << "Case #" << tc << ": " << y << " " << z << "\n";
    }
    return 0;
}
