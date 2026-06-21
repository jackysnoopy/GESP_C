#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> result;
    stack<int> stk;
    multiset<int> avail;
    int pushIdx = 0;
    for (int outCount = 0; outCount < n; outCount++) {
        while (!avail.empty() || pushIdx < n) {
            if (!avail.empty()) {
                auto it = avail.begin();
                if (stk.empty() || *it < stk.top() || (int)stk.size() >= c) {
                    result.push_back(*it);
                    avail.erase(it);
                    stk.pop();
                    break;
                }
            }
            if (pushIdx >= n) break;
            stk.push(a[pushIdx]);
            avail.insert(a[pushIdx]);
            pushIdx++;
            if ((int)stk.size() >= c) break;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << result[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
