#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> parent(N, -1);
    for (int i = 1; i < N; i++) {
        cin >> parent[i];
    }

    // 预处理每个节点的所有祖先（含自身）
    vector<vector<bool>> isAncestor(N, vector<bool>(N, false));
    for (int i = 0; i < N; i++) {
        int cur = i;
        while (cur != -1) {
            isAncestor[i][cur] = true;
            cur = parent[cur];
        }
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int m;
        cin >> m;
        vector<int> emp(m);
        for (int i = 0; i < m; i++) cin >> emp[i];

        vector<bool> common(N, true);
        for (int i = 0; i < N; i++) {
            if (!isAncestor[emp[0]][i]) common[i] = false;
        }
        for (int k = 1; k < m; k++) {
            for (int i = 0; i < N; i++) {
                if (common[i] && !isAncestor[emp[k]][i]) {
                    common[i] = false;
                }
            }
        }

        int ans = -1;
        for (int i = 0; i < N; i++) {
            if (common[i]) ans = i;
        }
        cout << ans << "\n";
    }

    return 0;
}
