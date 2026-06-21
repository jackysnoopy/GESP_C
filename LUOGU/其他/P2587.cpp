#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
int n, m;
int a[2001][2001], h[2001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            if (a[i][j] != a[i-1][j]) h[j] = 1;
            else h[j]++;
        stack<int> st;
        for (int j = 1; j <= m+1; j++) {
            while (!st.empty() && h[st.top()] > h[j]) {
                int tp = st.top(); st.pop();
                int w = j - (st.empty() ? 0 : st.top()) - 1;
                ans1 = max(ans1, min(h[tp], w));
                ans2 = max(ans2, h[tp] * w);
            }
            st.push(j);
        }
    }
    cout << ans1*ans1 << "\n" << ans2 << "\n";
    return 0;
}
