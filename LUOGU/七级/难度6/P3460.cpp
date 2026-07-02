#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) cin >> a[i];
    stack<int> stk;
    vector<int> ans;
    for (int i = 0; i < 2 * n; i++) {
        if (!stk.empty() && stk.top() == a[i]) {
            stk.pop();
        } else {
            stk.push(i + 1);
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << endl;
    for (int x : ans) cout << x << endl;
    return 0;
}