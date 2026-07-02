#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<pair<ll,ll>> grow,shr;
    for(int i=0;i<n;i++){ll a,b;cin>>a>>b; if(b>=a)grow.push_back({a,b}); else shr.push_back({a,b});}
    sort(grow.begin(),grow.end());
    sort(shr.begin(),shr.end(),[](const pair<ll,ll>&x,const pair<ll,ll>&y){return x.second>y.second;});
    ll req=0,free=0;
    for(auto&e:grow){ req=max(req,e.first-free); free+=e.second-e.first; }
    for(auto&e:shr){ req=max(req,e.first-free); free+=e.second-e.first; }
    cout<<req<<"\n";
    return 0;
}
