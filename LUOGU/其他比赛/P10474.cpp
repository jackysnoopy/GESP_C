#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

typedef unsigned long long ULL;
const ULL P1 = 131, P2 = 137;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M, N; cin >> M >> N;
    vector<string> mat(M);
    for (int i = 0; i < M; i++) cin >> mat[i];
    
    vector<ULL> pow1(N + 1, 1), pow2(M + 1, 1);
    for (int i = 1; i <= N; i++) pow1[i] = pow1[i-1] * P1;
    for (int i = 1; i <= M; i++) pow2[i] = pow2[i-1] * P2;
    
    vector<vector<ULL>> h(M + 1, vector<ULL>(N + 1, 0));
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            h[i][j] = h[i-1][j] * P2 + h[i][j-1] * P1 - h[i-1][j-1] * P1 * P2 + (mat[i-1][j-1] - '0');
    
    auto get_hash = [&](int x1, int y1, int x2, int y2) {
        return h[x2][y2] - h[x1-1][y2] * pow2[x2-x1+1] - h[x2][y1-1] * pow1[y2-y1+1] + h[x1-1][y1-1] * pow2[x2-x1+1] * pow1[y2-y1+1];
    };
    
    int Q; cin >> Q;
    while (Q--) {
        int A, B; cin >> A >> B;
        ULL target = 0;
        for (int i = 1; i <= A; i++) {
            string s; cin >> s;
            for (int j = 1; j <= B; j++)
                target = target * P1 + (s[j-1] - '0');
        }
        
        bool found = false;
        for (int i = 1; i + A - 1 <= M && !found; i++)
            for (int j = 1; j + B - 1 <= N && !found; j++)
                if (get_hash(i, j, i + A - 1, j + B - 1) == target)
                    found = true;
        cout << (found ? "1" : "0") << "\n";
    }
    return 0;
}