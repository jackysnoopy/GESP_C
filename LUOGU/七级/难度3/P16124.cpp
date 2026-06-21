#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    int counted = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] == 0 && i > 0 && p[i-1] == 1) counted++;
    }

    cout << counted << "\n";
    return 0;
}
