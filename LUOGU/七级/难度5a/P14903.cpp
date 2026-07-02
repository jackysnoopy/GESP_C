#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    
    multiset<int> cards(f.begin(), f.end());
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        auto it = cards.upper_bound(p[i]);
        if (it != cards.end()) {
            result.push_back(*it);
            cards.erase(it);
        } else {
            result.push_back(*cards.begin());
            cards.erase(cards.begin());
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    
    return 0;
}