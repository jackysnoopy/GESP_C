#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n,m;
vector<vector<int>> adj;
vector<int> seq,best,par;
vector<char> vis;
int ban_u=-1,ban_v=-1;
bool found=false; int cs,ce;
void dfsC(int u,int p){
    vis[u]=1; par[u]=p;
    for(int v:adj[u]){
        if(v==p) continue;
        if(!vis[v]){ dfsC(v,u); if(found)return; }
        else { cs=u; ce=v; found=true; return; }
    }
}
void dfs(int u,int p){
    vis[u]=1; seq.push_back(u);
    for(int v:adj[u]){
        if(v==p) continue;
        if((u==ban_u&&v==ban_v)||(u==ban_v&&v==ban_u)) continue;
        if(!vis[v]) dfs(v,u);
    }
}
void run(){
    fill(vis.begin(),vis.end(),0); seq.clear(); dfs(1,0);
    if(best.empty()||seq<best) best=seq;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>n>>m)) return 0;
    adj.assign(n+1,{}); vis.assign(n+1,0); par.assign(n+1,-1);
    for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);}
    for(int i=1;i<=n;i++) sort(adj[i].begin(),adj[i].end());
    if(m==n-1){ run(); }
    else{
        dfsC(1,0);
        vector<int> cyc; int u=cs;
        while(u!=ce){ cyc.push_back(u); u=par[u]; } cyc.push_back(ce);
        for(size_t i=0;i<cyc.size();i++){
            int a=cyc[i], b=cyc[(i+1)%cyc.size()];
            ban_u=a; ban_v=b; run();
        }
    }
    for(size_t i=0;i<best.size();i++) cout<<best[i]<<(i+1<best.size()?' ':'\n');
    return 0;
}
