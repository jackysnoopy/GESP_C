#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> chosen;

void dfs(int pos) {
    if (pos > n) {
        for (int x : chosen) cout << x << " ";
        cout << "\n";
        return;
    }
    // 不选
    dfs(pos + 1);
    // 选
    chosen.push_back(pos);
    dfs(pos + 1);
    chosen.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    dfs(1);
    return 0;
}