#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        stack<int> st;
        for (int i = 0; i < n; i++) {
            if (!st.empty() && st.top() == a[i]) {
                st.pop();
            } else {
                st.push(a[i]);
            }
        }
        int rem = st.size();
        cout << (rem + 1) / 2 << "\n";
    }
    return 0;
}
