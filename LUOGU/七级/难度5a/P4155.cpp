#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Arc{long long l,r;int id;};
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long M;
    if(!(cin>>n>>M)) return 0;
    vector<long long> C(n),D(n);
    for(int i=0;i<n;i++) cin>>C[i]>>D[i];
    vector<Arc> arcs;
    for(int i=0;i<n;i++){
        long long l=C[i], r=(D[i]>C[i]?D[i]:D[i]+M);
        arcs.push_back({l,r,i});
        arcs.push_back({l+M,r+M,i});
    }
    sort(arcs.begin(),arcs.end(),[](const Arc&a,const Arc&b){return a.l<b.l;});
    int m=arcs.size();
    vector<int> pmaxi(m);
    {int bi=0; long long br=arcs[0].r; for(int i=0;i<m;i++){ if(arcs[i].r>=br){br=arcs[i].r;bi=i;} pmaxi[i]=bi; }}
    vector<int> nxt(m);
    for(int i=0;i<m;i++){
        int lo=0,hi=m; while(lo<hi){int mid=(lo+hi)/2; if(arcs[mid].l<=arcs[i].r) lo=mid+1; else hi=mid;}
        nxt[i]=pmaxi[lo-1];
    }
    int LOG=20;
    vector<vector<int>> up(m,vector<int>(LOG+1));
    for(int i=0;i<m;i++) up[i][0]=nxt[i];
    for(int k=1;k<=LOG;k++) for(int i=0;i<m;i++) up[i][k]=up[up[i][k-1]][k-1];
    vector<int> startArc(n,-1);
    for(int i=0;i<m;i++) if(arcs[i].l<=M && startArc[arcs[i].id]==-1) startArc[arcs[i].id]=i;
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        int cur=startArc[i]; long long target=arcs[cur].l+M;
        if(arcs[cur].r>=target){ans[i]=1;continue;}
        int cnt=1;
        for(int k=LOG;k>=0;k--){ int nx=up[cur][k]; if(arcs[nx].r<target){cur=nx;cnt+=(1<<k);} }
        cnt++; ans[i]=cnt;
    }
    for(int i=0;i<n;i++) cout<<ans[i]<<(i+1<n?' ':'\n');
    return 0;
}
