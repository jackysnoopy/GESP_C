#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m;
vector<vector<pair<int,ll>>> g;
vector<ll> dn, upv;
ll ans=0;
void dfs1(int u,int p){
    dn[u]=0;
    for(auto&e:g[u]){int v=e.first;ll w=e.second;if(v==p)continue;dfs1(v,u);dn[u]=max(dn[u],w+dn[v]);}
}
void dfs2(int u,int p){
    vector<pair<ll,int>> ch;
    for(auto&e:g[u]){int v=e.first;ll w=e.second;if(v==p)continue;ch.push_back({w+dn[v],v});}
    int c=ch.size();
    vector<ll> pre(c+2,0),suf(c+2,0);
    for(int i=0;i<c;i++) pre[i+1]=max(pre[i],ch[i].first);
    for(int i=c-1;i>=0;i--) suf[i+1]=max(suf[i+2],ch[i].first);
    for(int i=0;i<c;i++){
        int v=ch[i].second; ll w=0;
        for(auto&e:g[u]) if(e.first==v){w=e.second;break;}
        ll other=max(upv[u],max(pre[i],suf[i+2]));
        upv[v]=w+other;
    }
    vector<ll> br;
    for(auto&x:ch) br.push_back(x.first);
    br.push_back(upv[u]);
    sort(br.rbegin(),br.rend());
    ll L1=br.size()>0?br[0]:0,L2=br.size()>1?br[1]:0,L3=br.size()>2?br[2]:0;
    ans=max(ans,L1+2*L2+L3);
    for(auto&e:g[u]){int v=e.first;if(v==p)continue;dfs2(v,u);}
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>n>>m)) return 0;
    g.assign(n+1,{}); dn.assign(n+1,0); upv.assign(n+1,0);
    for(int i=0;i<m;i++){int u,v;ll w;cin>>u>>v>>w;g[u].push_back({v,w});g[v].push_back({u,w});}
    dfs1(1,0); upv[1]=0; dfs2(1,0);
    cout<<ans<<"\n";
    return 0;
}
