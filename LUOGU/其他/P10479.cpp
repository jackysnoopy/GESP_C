#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int LA, LB, Q; string A, B;
    cin >> LA >> LB >> Q >> A >> B;
    
    // KMP next
    vector<int> nxt(LB + 1, 0);
    for (int i = 2, j = 0; i <= LB; i++) {
        while (j && B[i-1] != B[j]) j = nxt[j];
        if (B[i-1] == B[j]) j++;
        nxt[i] = j;
    }
    
    // KMP match
    vector<int> cnt(LB + 2, 0);
    for (int i = 0, j = 0; i < LA; i++) {
        while (j && A[i] != B[j]) j = nxt[j];
        if (A[i] == B[j]) j++;
        cnt[j]++;
        if (j == LB) j = nxt[j];
    }
    
    // 从长到短累加
    for (int i = LB; i >= 1; i--)
        cnt[nxt[i]] += cnt[i];
    
    while (Q--) {
        int x; cin >> x;
        cout << cnt[x] << "\n";
    }
    return 0;
}