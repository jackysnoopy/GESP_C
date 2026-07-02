#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        int maxSize = -1, maxIdx = -1;
        for (int i = 1; i <= n; i++) {
            int size, rate;
            cin >> size >> rate;
            int total = size + rate;
            if (total > maxSize) {
                maxSize = total;
                maxIdx = i;
            }
        }
        cout << maxIdx << "\n";
    }

    return 0;
}
