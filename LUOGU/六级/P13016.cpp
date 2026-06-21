#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cmath>
using namespace std;

vector<int> primes;

void sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) primes.push_back(i);
        for (int p : primes) {
            if (i * p > n) break;
            is_prime[i * p] = false;
            if (i % p == 0) break;
        }
    }
}

int spf(int x) {
    for (int p : primes) {
        if (p * p > x) break;
        if (x % p == 0) return p;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    sieve(31623);
    
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        
        unordered_set<int> path;
        int dep_x = 0, cur = x;
        while (cur > 1) {
            path.insert(cur);
            cur /= spf(cur);
            dep_x++;
        }
        path.insert(1);
        
        int dep_y = 0;
        cur = y;
        while (!path.count(cur)) {
            cur /= spf(cur);
            dep_y++;
        }
        int lca = cur;
        
        int dep_lca = 0;
        cur = lca;
        while (cur > 1) {
            cur /= spf(cur);
            dep_lca++;
        }
        
        cout << dep_x + dep_y - 2 * dep_lca << '\n';
    }
    
    return 0;
}
