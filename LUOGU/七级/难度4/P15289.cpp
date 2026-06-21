#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, d;
    cin >> n >> a >> d;

    vector<long long> b(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> b[i];

    int pos = a - 1;
    int rounds = 0;

    while (true) {
        int next_pos = -1;
        for (int x = -2; x <= 2; x++) {
            int new_pos = pos + x;
            if (new_pos >= 0 && new_pos < n - 1) {
                if (b[new_pos] > 2 * d + 1) {
                    next_pos = new_pos;
                    break;
                }
            }
        }

        if (next_pos == -1) break;

        for (int i = 0; i < n - 1; i++) {
            b[i] -= d;
        }

        rounds++;
        pos = next_pos;
    }

    cout << rounds << "\n";
    return 0;
}
