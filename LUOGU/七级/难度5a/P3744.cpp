#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<ll> x(n),y(n);
    for(int i=0;i<n;i++) cin>>x[i]>>y[i];
    ld ans=1e18;
    for(int i=0;i<n;i++){
        int a=(i-1+n)%n,b=(i+1)%n;
        ll dx=x[b]-x[a],dy=y[b]-y[a];
        ll px=x[i]-x[a],py=y[i]-y[a];
        ll cr=dx*py-dy*px;
        ld len=sqrtl((ld)dx*dx+(ld)dy*dy);
        ld d=fabsl((ld)cr)/len;
        if(d<ans) ans=d;
    }
    cout<<fixed<<setprecision(8)<<ans/2.0L<<"\n";
    return 0;
}
