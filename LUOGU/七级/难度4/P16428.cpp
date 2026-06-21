#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char c;
    int n, root, k;
    cin >> c >> n >> root >> k;

    vector<int> left(n + 1), right(n + 1);
    for (int i = 1; i <= n; i++) cin >> left[i] >> right[i];

    vector<int> result;

    if (c == 'A') {
        vector<int> stack;
        stack.push_back(root);
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            result.push_back(u);
            if (right[u]) stack.push_back(right[u]);
            if (left[u]) stack.push_back(left[u]);
        }
    } else if (c == 'B') {
        vector<int> stack;
        int cur = root;
        while (cur || !stack.empty()) {
            while (cur) {
                stack.push_back(cur);
                cur = left[cur];
            }
            cur = stack.back();
            stack.pop_back();
            result.push_back(cur);
            cur = right[cur];
        }
    } else {
        vector<int> stack;
        stack.push_back(root);
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            result.push_back(u);
            if (left[u]) stack.push_back(left[u]);
            if (right[u]) stack.push_back(right[u]);
        }
        reverse(result.begin(), result.end());
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}
