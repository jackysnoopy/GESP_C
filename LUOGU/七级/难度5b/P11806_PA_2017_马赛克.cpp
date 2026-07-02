#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<long long> x(n),y(n);
        for(int i=0;i<n;i++) cin>>x[i]>>y[i];
        vector<int> idx(n);
        for(int i=0;i<n;i++) idx[i]=i;
        sort(idx.begin(),idx.end(),[&](int a,int b){
            if(x[a]!=x[b]) return x[a]<x[b];
            return y[a]<y[b];
        });
        bool ok=true;
        vector<long long> ans(n,0);
        for(int i=0;i<n;i++){
            long long minR=x[idx[i]];
            long long maxR=x[idx[i]];
            long long maxTop=y[idx[i]];
            for(int j=i+1;j<n;j++){
                if(y[idx[j]]<y[idx[i]]){
                    ok=false;
                    break;
                }
                if(x[idx[j]]>=maxR){
                    maxR=x[idx[j]];
                    maxTop=max(maxTop,y[idx[j]]);
                }
            }
            if(!ok) break;
            ans[idx[i]]=max(maxR-x[idx[i]],maxTop-y[idx[i]]);
            if(ans[idx[i]]==0) ans[idx[i]]=1;
        }
        if(!ok){
            cout<<"NIE\n";
        } else {
            cout<<"TAK";
            for(int i=0;i<n;i++) cout<<" "<<ans[i];
            cout<<"\n";
        }
    }
    return 0;
}
