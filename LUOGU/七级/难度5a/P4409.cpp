#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int n; vector<ll> a;
bool check(ll C){
    ll mx=a[0]; ll lo=mx, hi=mx; // L_1 = a[0] (low colors used by general 1)
    for(int i=1;i<n;i++){
        ll nlo = max(0LL, a[i] - (C - mx) + a[i-1] - hi);
        ll nhi = min((ll)a[i], mx - lo);
        if(nlo>nhi) return false;
        lo=nlo; hi=nhi;
    }
    return lo<=0 && 0<=hi;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>n)) return 0;
    a.assign(n,0);
    for(int i=0;i<n;i++) cin>>a[i];
    // rotate so general with max a is first
    int p=max_element(a.begin(),a.end())-a.begin();
    vector<ll> b(n);
    for(int i=0;i<n;i++) b[i]=a[(i+p)%n];
    a=b;
    ll lo=*max_element(a.begin(),a.end());
    ll edge=0; for(int i=0;i<n;i++) edge=max(edge,a[i]+a[(i+1)%n]);
    lo=max(lo,edge);
    ll hi=0; for(int i=0;i<n;i++) hi+=a[i];
    while(lo<hi){ ll mid=(lo+hi)/2; if(check(mid)) hi=mid; else lo=mid+1; }
    cout<<lo<<"\n";
    return 0;
}
