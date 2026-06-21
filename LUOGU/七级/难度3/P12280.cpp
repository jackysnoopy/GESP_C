#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    set<int> st;
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (st.count(a[i])) break;
        st.insert(a[i]);
        p = i;
    }
    int ans = p;
    int j = n + 1;
    for (int i = p; i >= 0; i--) {
        while (j > i + 1 && !st.count(a[j - 1])) {
            j--;
            st.insert(a[j]);
        }
        ans = max(ans, i + (n - j + 1));
        if (i >= 1) st.erase(a[i]);
    }
    cout << ans << "\n";
    return 0;
}
