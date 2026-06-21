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
        int n, m;
        cin >> n >> m;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int segments = 0;
        int i = 0;

        while (i < n) {
            segments++;
            int j = i;
            while (j < n - 1 && a[j + 1] - a[i] <= m) j++;
            i = j + 1;
        }

        cout << segments << "\n";
    }

    return 0;
}
