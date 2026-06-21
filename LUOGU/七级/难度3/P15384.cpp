#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> tree(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        tree[p].push_back(i);
    }

    int leaves = 0;
    for (int i = 0; i < n; i++) {
        if (tree[i].empty()) leaves++;
    }

    cout << leaves << "\n";
    return 0;
}
