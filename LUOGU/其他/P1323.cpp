#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, m;
    cin >> k >> m;
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    pq.push(1);
    string num = "";
    while ((int)num.size() < k) {
        long long v = pq.top(); pq.pop();
        num += to_string(v);
        long long v1 = 2 * v + 1;
        long long v2 = 4 * v + 5;
        pq.push(v1);
        pq.push(v2);
    }
    num = num.substr(0, k);
    cout << num << "\n";
    // Remove m digits to maximize
    string res = "";
    int rem = m;
    for (char c : num) {
        while (!res.empty() && rem > 0 && res.back() < c) {
            res.pop_back(); rem--;
        }
        res.push_back(c);
    }
    res.resize(res.size() - rem);
    cout << res << "\n";
    return 0;
}
