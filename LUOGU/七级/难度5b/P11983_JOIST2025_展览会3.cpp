#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,M;
    cin>>N>>M;
    vector<int> A(N);
    for(int i=0;i<N;i++) cin>>A[i];
    vector<int> L(M),R(M);
    for(int i=0;i<M;i++) cin>>L[i]>>R[i];
    vector<int> order(M);
    for(int i=0;i<M;i++) order[i]=i;
    sort(order.begin(),order.end(),[&](int a,int b){
        return L[a]<L[b];
    });
    vector<int> ans(M);
    vector<int> used(N,0);
    for(int idx:order){
        int l=L[idx]-1,r=R[idx]-1;
        int best=0;
        for(int i=l;i<=r;i++){
            if(!used[i] && A[i]>best) best=A[i];
        }
        ans[idx]=best;
        for(int i=l;i<=r;i++){
            if(A[i]==best && !used[i]){
                used[i]=1;
                break;
            }
        }
    }
    for(int i=0;i<M;i++) cout<<ans[i]<<"\n";
    return 0;
}
