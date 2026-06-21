#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        string r;
        cin >> r;

        int len = r.size();
        int min_ones = 0, max_ones = 0;

        for (int i = 0; i < len; i++) {
            if (r[i] == '1') {
                min_ones++;
                max_ones++;
            }
        }

        cout << min_ones << " " << max_ones << "\n";
    }

    return 0;
}
