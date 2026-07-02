#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int,int>> drives(n);
    for (int i = 0; i < n; i++) {
        cin >> drives[i].first >> drives[i].second;
    }
    
    // 贪心：先处理b>=a的（按a升序），再处理b<a的（按b降序）
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    
    sort(order.begin(), order.end(), [&](int i, int j) {
        int ai = drives[i].first, bi = drives[i].second;
        int aj = drives[j].first, bj = drives[j].second;
        bool gi = (bi >= ai), gj = (bj >= aj);
        if (gi != gj) return gi > gj;
        if (gi) return ai < aj;
        return bi > bj;
    });
    
    long long freeSpace = 0;
    long long need = 0;
    
    for (int idx : order) {
        int a = drives[idx].first, b = drives[idx].second;
        if (freeSpace < a) {
            need += a - freeSpace;
            freeSpace = a;
        }
        freeSpace -= a;
        freeSpace += b;
    }
    
    cout << need << endl;
    return 0;
}
