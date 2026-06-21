#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    m--;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    int out_cnt = 0, in_cnt = 0;
    for (int j = 0; j < n; j++)
        if (a[m][j]) out_cnt++;
    for (int i = 0; i < n; i++)
        if (a[i][m]) in_cnt++;
    cout << out_cnt << " " << in_cnt << " " << out_cnt + in_cnt << "\n";
    return 0;
}
