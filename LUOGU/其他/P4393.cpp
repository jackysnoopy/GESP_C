#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    stack<int> st;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while (!st.empty() && st.top() <= x) {
            ans += st.top();
            st.pop();
        }
        if (!st.empty()) ans += x;
        st.push(x);
    }
    while (st.size() > 1) {
        int top = st.top();
        st.pop();
        ans += st.top();
    }
    cout << ans << "\n";
    return 0;
}
