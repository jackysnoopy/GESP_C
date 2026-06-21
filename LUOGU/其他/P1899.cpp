#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, P;
    cin >> N >> P;
    vector<int> normal;
    vector<pair<int,int>> magic;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        if (cin.peek() == ' ') { int y; cin >> y; magic.push_back({x,y}); }
        else normal.push_back(x);
    }
    sort(normal.begin(), normal.end(), greater<int>());
    sort(magic.begin(), magic.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second-a.first > b.second-b.first;
    });
    long long money = 0;
    int idx = 0;
    while (idx < (int)normal.size() && money >= normal[idx]) { money += normal[idx]; idx++; }
    for (int i = 0; i < (int)magic.size(); i++) {
        if (money >= P) { money -= P; money += magic[i].second; }
        else break;
    }
    while (idx < (int)normal.size() && money >= normal[idx]) { money += normal[idx]; idx++; }
    cout << money << endl;
    return 0;
}