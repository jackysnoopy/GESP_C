#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> dance(n);
    for (int i = 0; i < n; i++) cin >> dance[i];

    sort(dance.rbegin(), dance.rend());

    int score = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) score += dance[i];
    }

    cout << score << "\n";
    return 0;
}
