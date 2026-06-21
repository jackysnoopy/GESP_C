#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef unsigned long long ULL;
const ULL P = 131;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C; cin >> R >> C;
    vector<string> mat(R);
    for (int i = 0; i < R; i++) cin >> mat[i];
    
    // 行哈希
    vector<ULL> row_hash(R, 0);
    for (int i = 0; i < R; i++)
        for (char c : mat[i])
            row_hash[i] = row_hash[i] * P + c;
    
    // 列哈希
    vector<ULL> col_hash(C, 0);
    for (int j = 0; j < C; j++)
        for (int i = 0; i < R; i++)
            col_hash[j] = col_hash[j] * P + mat[i][j];
    
    // 找行最小周期
    auto min_period = [](const vector<ULL>& a) {
        int n = a.size();
        for (int p = 1; p <= n; p++) {
            if (n % p != 0) continue;
            bool ok = true;
            for (int i = p; i < n && ok; i++)
                if (a[i] != a[i % p]) ok = false;
            if (ok) return p;
        }
        return n;
    };
    
    int rp = min_period(row_hash);
    int cp = min_period(col_hash);
    
    cout << rp * cp << "\n";
    return 0;
}