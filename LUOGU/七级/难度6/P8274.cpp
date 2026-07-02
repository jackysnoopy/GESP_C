#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> children[MAXN];
int l[MAXN], r[MAXN];
int n;
int ans;
int s[MAXN];

void dfs(int u) {
    for (int v : children[u]) {
        dfs(v);
    }
    
    // Binary search for optimal balance
    int low = l[u], high = r[u];
    while (low < high) {
        int mid = (low + high) / 2;
        
        // Check if this value works
        bool valid = true;
        for (int v : children[u]) {
            if (s[v] < mid - ans || s[v] > mid + ans) {
                valid = false;
                break;
            }
        }
        
        if (valid) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    s[u] = low;
}

bool check(int mid) {
    ans = mid;
    dfs(1);
    
    for (int i = 1; i <= n; i++) {
        if (s[i] < l[i] || s[i] > r[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, B;
    cin >> T >> B;
    
    while (T--) {
        cin >> n;
        
        for (int i = 1; i <= n; i++) {
            children[i].clear();
        }
        
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            children[p].push_back(i);
        }
        
        for (int i = 1; i <= n; i++) {
            cin >> l[i] >> r[i];
        }
        
        int low = 0, high = 1e9;
        while (low < high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        check(low);
        cout << low << endl;
        
        if (B == 1) {
            for (int i = 1; i <= n; i++) {
                cout << s[i] << (i == n ? "\n" : " ");
            }
        }
    }
    
    return 0;
}