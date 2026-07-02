#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int lt,ls; if(!(cin>>lt>>ls)) return 0;
    string T,S; cin>>T>>S;
    string c=T+string(1,'#')+S;
    int n=c.size();
    vector<int> Z(n,0);
    Z[0]=n;
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(i<r) Z[i]=min(r-i, Z[i-l]);
        while(i+Z[i]<n && c[Z[i]]==c[i+Z[i]]) Z[i]++;
        if(i+Z[i]>r){ l=i; r=i+Z[i]; }
    }
    int ts=lt+1; // S starts at index ts
    // p[i] = max jump from S-position i = Z[ts+i]
    // jump game II: min segments to reach end
    int m=ls;
    if(m==0){ cout<<0<<"\n"; return 0; }
    int jumps=0, curEnd=0, curFar=0;
    for(int i=0;i<m;i++){
        int p=Z[ts+i];
        if(i+ (ll)p > curFar) curFar=i+p;
        if(curFar>=m){ cout<<jumps+1<<"\n"; return 0; }
        if(i==curEnd){
            if(curFar<=curEnd && i<m-1){ cout<<"Fake\n"; return 0; }
            jumps++; curEnd=curFar;
        }
    }
    cout<<"Fake\n";
    return 0;
}
