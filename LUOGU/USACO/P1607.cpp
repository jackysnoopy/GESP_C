#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int K, N, C;
    cin >> K >> N >> C;
    vector<tuple<int,int,int>> g(K);
    for (int i = 0; i < K; i++) { int s,e,m; cin>>s>>e>>m; g[i]=make_tuple(e,s,m); }
    sort(g.begin(), g.end());
    vector<int> cap(N+2,0);
    long long ans=0;
    for(int i=0;i<K;i++){
        int e=get<0>(g[i]),s=get<1>(g[i]),m=get<2>(g[i]);
        int mn=C;
        for(int j=s;j<e;j++) mn=min(mn,C-cap[j]);
        int take=min(m,mn);
        if(take>0){ans+=take;for(int j=s;j<e;j++)cap[j]+=take;}
    }
    cout<<ans<<endl;
    return 0;
}