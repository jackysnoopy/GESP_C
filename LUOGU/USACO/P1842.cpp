#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Cow {
    int w, s;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++)
        cin >> cows[i].w >> cows[i].s;
    
    sort(cows.begin(), cows.end(), [](const Cow& a, const Cow& b) {
        return a.w + a.s < b.w + b.s;
    });
    
    long long sum = 0, ans = LLONG_MIN;
    for (const auto& cow : cows) {
        ans = max(ans, sum - cow.s);
        sum += cow.w;
    }
    
    cout << ans << "\n";
    return 0;
}