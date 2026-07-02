#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5e5 + 10;

int n;
int X[MAXN], L[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> X[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> L[i];
    }
    
    // 将比赛按照L[i]排序
    vector<pair<int, int>> competitions;
    for (int i = 1; i <= n; i++) {
        competitions.push_back({L[i], X[i]});
    }
    sort(competitions.begin(), competitions.end());
    
    // 贪心：每次选择能参加的比赛中X[i]最小的
    long long currentLevel = 0;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (currentLevel <= competitions[i].first) {
            currentLevel += competitions[i].second;
            count++;
        }
    }
    
    cout << count << '\n';
    
    return 0;
}