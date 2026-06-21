#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];

    vector<int> count(m + 1, 0);
    int unique = 0;
    int segments = 0;

    for (int i = 0; i < n; i++) {
        if (count[t[i]] == 0) unique++;
        count[t[i]]++;

        if (unique == m) {
            segments++;
            fill(count.begin(), count.end(), 0);
            unique = 0;
        }
    }

    cout << segments << "\n";
    return 0;
}
