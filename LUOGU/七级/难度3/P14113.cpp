#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int maxCnt = 1, cnt = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) cnt++;
        else cnt = 1;
        maxCnt = max(maxCnt, cnt);
    }

    cout << maxCnt << "\n";
    return 0;
}
