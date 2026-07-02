#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,b; if(!(cin>>n>>b)) return 0;
    vector<long long> f(n);
    for(int i=0;i<n;i++) cin>>f[i];
    struct Boot{long long s,d;int id;};
    vector<Boot> boots(b);
    for(int i=0;i<b;i++){cin>>boots[i].s>>boots[i].d;boots[i].id=i;}
    sort(boots.begin(),boots.end(),[](const Boot&a,const Boot&b){return a.s>b.s;});
    vector<int> idx; for(int i=1;i<n-1;i++) idx.push_back(i);
    sort(idx.begin(),idx.end(),[&](int x,int y){return f[x]>f[y];});
    vector<char> blocked(n,0);
    vector<int> fa(n),sz(n);
    for(int i=0;i<n;i++){fa[i]=i;sz[i]=1;}
    function<int(int)> find=[&](int x){return fa[x]==x?x:fa[x]=find(fa[x]);};
    long long maxrun=0; vector<int> ans(b); int ptr=0;
    for(auto&bt:boots){
        while(ptr<(int)idx.size() && f[idx[ptr]]>bt.s){
            int p=idx[ptr++]; blocked[p]=1;
            if(p-1>=0&&blocked[p-1]){int a=find(p),c=find(p-1);if(a!=c){fa[a]=c;sz[c]+=sz[a];}}
            if(p+1<n&&blocked[p+1]){int a=find(p),c=find(p+1);if(a!=c){fa[a]=c;sz[c]+=sz[a];}}
            long long r=sz[find(p)]; if(r>maxrun)maxrun=r;
        }
        long long maxgap=(maxrun>0?maxrun+1:1);
        ans[bt.id]=(maxgap<=bt.d)?1:0;
    }
    for(int i=0;i<b;i++) cout<<ans[i]<<"\n";
    return 0;
}
