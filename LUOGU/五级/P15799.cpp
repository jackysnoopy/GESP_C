#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    unordered_set<int> st;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        st.insert(x);
    }
    
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        if (st.count(x)) ans++;
    }
    
    cout << ans << '\n';
    return 0;
}