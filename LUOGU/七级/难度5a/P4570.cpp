#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<pair<ll,ll>> a(n);
    for(int i=0;i<n;i++) cin>>a[i].first>>a[i].second;
    sort(a.begin(),a.end(),[](const pair<ll,ll>&x,const pair<ll,ll>&y){return x.second>y.second;});
    vector<ll> b(61,0); ll ans=0;
    for(auto&e:a){
        ll x=e.first;
        for(int i=60;i>=0;i--){
            if(!((x>>i)&1)) continue;
            if(b[i]==0){ b[i]=x; ans+=e.second; break; }
            x^=b[i];
        }
    }
    cout<<ans<<"\n";
    return 0;
}
