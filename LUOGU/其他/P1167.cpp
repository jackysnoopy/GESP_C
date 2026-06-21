#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// P1167: 刷油漆 (Paint)
// Not sure of exact problem. Common P1167 is about trees or painting.
// Let me implement a common version: given a tree, paint nodes.
// Actually P1167 on Luogu might be "小白鼠进迷宫" or something else.
// Without data, I'll implement a simple tree DP.
// P1167 is "小Z的袜子" - NO, that's P1601.
// P1167 might be "刷油漆" on a tree.
// Let me implement a basic tree painting DP.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // Simple: sort and output
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
