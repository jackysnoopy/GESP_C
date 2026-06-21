#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int N,M;
    if(scanf("%d %d",&N,&M)!=2) return 0;
    vector<int> A(N),B(N),C(M),D(M);
    for(int i=0;i<N;i++) scanf("%d",&A[i]);
    for(int i=0;i<N;i++) scanf("%d",&B[i]);
    for(int j=0;j<M;j++) scanf("%d",&C[j]);
    for(int j=0;j<M;j++) scanf("%d",&D[j]);
    vector<vector<long long>> bBy(N+1), dBy(N+1);
    for(int i=0;i<N;i++) bBy[A[i]].push_back(B[i]);
    for(int j=0;j<M;j++) dBy[C[j]].push_back(D[j]);
    vector<long long> marg;
    for(int br=1;br<=N;br++){
        if(bBy[br].empty()) continue;
        sort(bBy[br].begin(),bBy[br].end(),greater<long long>());
        int tb=(int)dBy[br].size();
        if(tb>0) sort(dBy[br].begin(),dBy[br].end(),greater<long long>());
        int nb=(int)bBy[br].size();
        for(int k=1;k<=nb;k++){
            long long g=bBy[br][k-1];
            if(k<=tb) g+=dBy[br][k-1];
            marg.push_back(g);
        }
    }
    sort(marg.begin(),marg.end(),greater<long long>());
    long long ans=0;
    for(int i=0;i<M;i++) ans+=marg[i];
    printf("%lld\n",ans);
    return 0;
}
