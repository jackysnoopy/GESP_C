#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> rings(n);
    for (int i = 0; i < n; i++) cin >> rings[i];

    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += rings[i];
    }

    cout << total << "\n";
    return 0;
}
