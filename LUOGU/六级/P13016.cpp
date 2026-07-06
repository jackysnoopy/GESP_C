#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXP = 31623;
vector<int> primes;
bool isComposite[MAXP + 1];

void initPrimes() {
    for (int i = 2; i <= MAXP; ++i) {
        if (!isComposite[i]) primes.push_back(i);
        for (int p : primes) {
            if (i * p > MAXP) break;
            isComposite[i * p] = true;
            if (i % p == 0) break;
        }
    }
}

int getMinPrimeFactor(int n) {
    for (int p : primes) {
        if (p * p > n) break;
        if (n % p == 0) return p;
    }
    return n;
}

int getParent(int n) {
    if (n == 1) return 0;
    return n / getMinPrimeFactor(n);
}

int getDepth(int n) {
    int depth = 0;
    while (n > 1) {
        n = getParent(n);
        depth++;
    }
    return depth;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    initPrimes();
    
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        
        // 记录x的路径
        unordered_set<int> pathX;
        int temp = x;
        while (temp > 1) {
            pathX.insert(temp);
            temp = getParent(temp);
        }
        pathX.insert(1);
        
        // 找y的路径中第一个出现在x路径中的节点
        temp = y;
        int lca = 1;
        while (temp >= 1) {
            if (pathX.count(temp)) {
                lca = temp;
                break;
            }
            if (temp == 1) break;
            temp = getParent(temp);
        }
        
        // 计算深度
        int depthX = getDepth(x);
        int depthY = getDepth(y);
        int depthLCA = getDepth(lca);
        
        cout << depthX + depthY - 2 * depthLCA << endl;
    }
    
    return 0;
}