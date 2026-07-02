#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    int m=2*n;
    vector<ll> s(m);
    map<ll,int> leftPos, rightPos; // size -> position
    for(int i=0;i<m;i++){
        cin>>s[i];
        ll sz=s[i]<0?-s[i]:s[i];
        if(s[i]<0) leftPos[sz]=i; else rightPos[sz]=i;
    }
    vector<int> pos(m);
    vector<char> used(m,0);
    int k=0;
    for(int i=0;i<m;i++){
        if(used[i]) continue;
        ll sz=s[i]<0?-s[i]:s[i];
        int lp, rp;
        if(s[i]<0){ lp=i; rp=rightPos[sz]; }
        else { rp=i; lp=leftPos[sz]; }
        pos[2*k]=lp; pos[2*k+1]=rp;
        used[lp]=used[rp]=1;
        k++;
    }
    // inversions of pos
    vector<int> bit(m+2,0);
    auto add=[&](int x){for(x++;x<=m+1;x+=x&-x)bit[x]++;};
    auto qry=[&](int x){int r=0;for(x++;x>0;x-=x&-x)r+=bit[x];return r;};
    ll ans=0;
    for(int t=0;t<m;t++){ ans+=(ll)(t-qry(pos[t])); add(pos[t]); }
    cout<<ans<<"\n";
    return 0;
}
