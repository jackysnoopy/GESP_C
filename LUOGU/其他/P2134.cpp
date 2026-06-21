#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Line { ll m, b; ll eval(ll x) { return m*x+b; } };
vector<Line> hull;
bool bad(Line l1, Line l2, Line l3) {
    __int128 left = (__int128)(l2.b-l1.b)*(l2.m-l3.m);
    __int128 right = (__int128)(l3.b-l2.b)*(l1.m-l2.m);
    return left >= right;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, p, q;
    cin >> n >> p >> q;
    vector<ll> d0(n+1), d1(n+1);
    d0[0] = (ll)1e18; d1[0] = 0;
    ll minR = d0[0];
    hull.push_back({0, d1[0]});
    for (int i = 1; i <= n; i++) {
        d1[i] = q*i + minR;
        while (hull.size()>=2 && hull[hull.size()-2].eval(i)>=hull[hull.size()-1].eval(i))
            hull.pop_back();
        d0[i] = p*i*i + hull.back().eval(i);
        if (i < n) {
            Line nl = {-2LL*p*i, d1[i]+(ll)p*i*i};
            while (hull.size()>=2 && bad(hull[hull.size()-2], hull[hull.size()-1], nl))
                hull.pop_back();
            hull.push_back(nl);
        }
        minR = min(minR, d0[i]-q*i);
    }
    cout << min(d0[n], d1[n]) << "\n";
    return 0;
}
