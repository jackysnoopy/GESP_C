#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll T;
    if(!(cin>>n>>T)) return 0;
    vector<ll> e(n);
    for(int i=0;i<n;i++){ ll p,s; cin>>p>>s; e[i]=p+s*T; }
    // min lanes = length of longest non-increasing subsequence of e
    // = longest non-decreasing subsequence of -e
    vector<ll> d; // ascending
    for(int i=0;i<n;i++){
        ll x=-e[i];
        auto it=upper_bound(d.begin(),d.end(),x);
        if(it==d.end()) d.push_back(x); else *it=x;
    }
    cout<<d.size()<<"\n";
    return 0;
}
