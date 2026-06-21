#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L, M;
    cin >> n >> L >> M;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ops = 0;
    int last_locked = -1;

    for (int i = 0; i < n; i++) {
        if (a[i] >= M) continue;

        int need = M - a[i];
        ops += need + 1;
    }

    cout << ops << "\n";
    return 0;
}
