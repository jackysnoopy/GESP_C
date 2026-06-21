#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    set<pair<int,int>> st;
    st.insert({a[0], 1});
    
    for (int i = 1; i < n; i++) {
        auto it = st.lower_bound({a[i], 0});
        int diff = INT_MAX, pos = -1;
        if (it != st.end()) {
            diff = abs(it->first - a[i]);
            pos = it->second;
        }
        if (it != st.begin()) {
            --it;
            int d = abs(it->first - a[i]);
            if (d < diff || (d == diff && it->second < pos)) {
                diff = d; pos = it->second;
            }
        }
        cout << diff << " " << pos << "\n";
        st.insert({a[i], i + 1});
    }
    return 0;
}