#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<ll> c(n);
    for(int i=0;i<n;i++) cin>>c[i];
    ll P=0,mn=0,mnidx=-1;
    for(int i=0;i<n;i++){ P+=c[i]-1; if(P<mn){mn=P;mnidx=i;} }
    int s=(mnidx+1)%n;
    ll cost=0,E=0;
    for(int t=0;t<n;t++){ int i=(s+t)%n; E+=c[i]-1; cost+=E*E; }
    cout<<cost<<"\n";
    return 0;
}
