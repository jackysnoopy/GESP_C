#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll W;
    if(!(cin>>n>>W)) return 0;
    vector<ll> T(n);
    for(int i=0;i<n;i++) cin>>T[i];
    sort(T.begin(),T.end());
    // Maximum: zigzag between extremes; can insert water (W) freely.
    // Max sum achieved by alternating current between extremes.
    // Place cookies in order: min,max,2nd-min,2nd-max,... ; start with water W.
    // But simpler known: max = sum over sorted by visiting extremes alternating.
    ll mx=0;
    {
        int lo=0, hi=n-1; ll cur=W; bool takeHi=true;
        // build sequence: take from hi then lo alternating to maximize |diff|
        vector<ll> seq;
        while(lo<=hi){
            if(takeHi) seq.push_back(T[hi--]); else seq.push_back(T[lo++]);
            takeHi=!takeHi;
        }
        cur=W;
        for(ll x:seq){ mx+=abs(x-cur); cur=x; }
        // also try starting with lo
        lo=0;hi=n-1;cur=W;takeHi=false; ll mx2=0;
        vector<ll> seq2;
        while(lo<=hi){ if(takeHi)seq2.push_back(T[hi--]);else seq2.push_back(T[lo++]); takeHi=!takeHi; }
        cur=W; for(ll x:seq2){mx2+=abs(x-cur);cur=x;}
        mx=max(mx,mx2);
    }
    // Minimum: sort ascending, go from one end, use water to "reset" when beneficial.
    // Walk sorted; each adjacent pair contributes min(diff, |Ti-W|+|Ti+1-W|) reset cost.
    ll mn=0;
    {
        // first cookie cost vs water
        ll cur=W;
        // We can choose to reset (use water) between any two adjacent cookies.
        // Process cookies in sorted order; between prev and next, choose min(direct diff, reset via water).
        ll prev = T[0];
        mn += min(abs(T[0]-W), abs(T[0]-cur)); // first: either start from water or current
        cur = T[0];
        for(int i=1;i<n;i++){
            ll direct = abs(T[i]-cur);
            ll reset = abs(cur-W) + abs(T[i]-W);
            if(reset < direct){ mn += abs(cur-W) + abs(T[i]-W); }
            else { mn += direct; }
            cur = T[i];
        }
    }
    cout<<mn<<" "<<mx<<"\n";
    return 0;
}
