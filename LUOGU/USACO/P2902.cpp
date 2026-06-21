#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c;
    cin >> n >> c;
    vector<int> cnt(c + 1);
    for (int i = 1; i <= c; i++) cin >> cnt[i];
    vector<pair<int,int>> result;
    vector<int> pool;
    for (int i = 1; i <= c; i++)
        for (int j = 0; j < cnt[i]; j++) pool.push_back(i);
    int i = 0, j = 1;
    while ((int)result.size() < n / 2) {
        if (pool[i] != pool[j]) {
            result.push_back(make_pair(pool[i], pool[j]));
            pool.erase(pool.begin() + j);
            if (j >= (int)pool.size()) j = i + 1;
        } else {
            j++;
            if (j >= (int)pool.size()) {
                i++;
                j = i + 1;
            }
        }
    }
    for (int ii = 0; ii < (int)result.size(); ii++)
        cout << result[ii].first << " " << result[ii].second << "\n";
    return 0;
}
