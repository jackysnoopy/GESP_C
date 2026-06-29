#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].first >> cows[i].second;
    }
    
    sort(cows.begin(), cows.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
    
    long long up_time = 0;
    long long down_time = 0;
    
    for (int i = 0; i < n; i++) {
        up_time += cows[i].first;
        down_time = max(down_time, up_time) + cows[i].second;
    }
    
    cout << down_time << "\n";
    return 0;
}