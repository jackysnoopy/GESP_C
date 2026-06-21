#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
struct Stone { long long x,y,m,p,r; int id; };
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long x0,y0,m0,p0,r0; cin>>x0>>y0>>m0>>p0>>r0;
    int n; cin>>n;
    vector<Stone> stones(n);
    for(int i=0;i<n;++i) { cin>>stones[i].x>>stones[i].y>>stones[i].m>>stones[i].p>>stones[i].r; stones[i].id=i; }
    vector<Stone> pool=stones;
    sort(pool.begin(),pool.end(),[](const Stone&a,const Stone&b){return a.m<b.m;});
    int sz=(int)sqrt(n)+1;
    int ans=0;
    vector<bool> vis(n,false);
    queue<Stone> q;
    Stone start={x0,y0,m0,p0,r0,-1};
    auto reachable=[&](Stone &s,Stone &t)->bool{
        long long dx=s.x-t.x,dy=s.y-t.y;
        return dx*dx+dy*dy<=s.r*s.r && t.m<=s.p;
    };
    vector<Stone> cur={start};
    while(!cur.empty()){
        vector<Stone> nextPool;
        for(auto&s:cur){
            for(auto&t:pool){
                if(vis[t.id]) continue;
                if(reachable(s,t)){ vis[t.id]=true; nextPool.push_back(t); ans++; }
            }
        }
        cur=nextPool;
    }
    cout<<ans<<'\n';
    return 0;
}
