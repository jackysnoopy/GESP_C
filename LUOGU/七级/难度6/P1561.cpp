#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    // Johnson's rule
    vector<pair<int,int>> A, B;
    for (auto& p : a) {
        if (p.first <= p.second) A.push_back(p);
        else B.push_back(p);
    }
    sort(A.begin(), A.end(), [](const pair<int,int>& x, const pair<int,int>& y){
        return x.first < y.first;
    });
    sort(B.begin(), B.end(), [](const pair<int,int>& x, const pair<int,int>& y){
        return x.second > y.second;
    });
    vector<pair<int,int>> ord;
    for (auto& p : A) ord.push_back(p);
    for (auto& p : B) ord.push_back(p);
    long long t1 = 0, t2 = 0;
    for (auto& p : ord) {
        t1 += p.first;
        t2 = max(t2, t1) + p.second;
    }
    cout << t2 << "\n";
    return 0;
}
