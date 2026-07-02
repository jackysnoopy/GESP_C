#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m; ll L;
vector<vector<pair<int,int>>> g;
int cnt;
ll dfs(int u,int fa){
    multiset<ll> s;
    for(auto&e:g[u]){
        int v=e.first; ll w=e.second;
        if(v==fa) continue;
        ll t=dfs(v,u)+w;
        s.insert(t);
    }
    ll ret=0;
    while(!s.empty()){
        if(*s.begin()>=L){ cnt+=(int)s.size(); return 0; }
        ll x=*s.begin(); s.erase(s.begin());
        auto it=s.lower_bound(L-x);
        if(it!=s.end()){ cnt++; s.erase(it); }
        else ret=max(ret,x);
    }
    return ret;
}
bool check(ll lim){
    L=lim; cnt=0; dfs(1,0);
    return cnt>=m;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>n>>m)) return 0;
    g.assign(n+1,{});
    ll sum=0;
    for(int i=0;i<n-1;i++){int u,v;ll w;cin>>u>>v>>w;g[u].push_back({v,w});g[v].push_back({u,w});sum+=w;}
    ll lo=1,hi=sum,ans=0;
    while(lo<=hi){ll mid=(lo+hi)/2; if(check(mid)){ans=mid;lo=mid+1;}else hi=mid-1;}
    cout<<ans<<"\n";
    return 0;
}
