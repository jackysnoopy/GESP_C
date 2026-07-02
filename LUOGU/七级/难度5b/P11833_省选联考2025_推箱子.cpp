#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c,T;
    cin>>c>>T;
    while(T--){
        int n;
        cin>>n;
        vector<long long> a(n),b(n),t(n);
        for(int i=0;i<n;i++) cin>>a[i]>>b[i]>>t[i];
        bool ok=true;
        for(int i=0;i<n;i++){
            long long dist=b[i]-a[i];
            if(dist<0) dist=-dist;
            if(t[i]<dist){
                ok=false;
                break;
            }
        }
        cout<<(ok?"Yes":"No")<<"\n";
    }
    return 0;
}
