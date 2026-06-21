#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

struct BIT {
    int n;
    vector<int> tree;
    BIT(int n_) : n(n_), tree(n_ + 1, 0) {}
    void add(int i, int v) {
        for (; i <= n; i += i & -i) tree[i] += v;
    }
    int sum(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) res += tree[i];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    BIT bit(N);
    long long ans = 0;
    
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        ans += bit.sum(x);
        bit.add(x + 1, 1);
    }
    
    cout << ans << "\n";
    return 0;
}
