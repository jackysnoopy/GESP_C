#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    vector<int> l(n),r(n);
    for(int i=0;i<n;i++) cin>>l[i]>>r[i];
    int maxCoord=2*n;
    vector<int> cnt(maxCoord+2,0);
    for(int i=0;i<n;i++){
        cnt[l[i]]++;
        cnt[r[i]+1]--;
    }
    int cur=0,maxVal=0;
    for(int i=1;i<=maxCoord;i++){
        cur+=cnt[i];
        maxVal=max(maxVal,cur);
    }
    cout<<maxVal<<"\n";
    string s(n,'1');
    cout<<s<<"\n";
    return 0;
}
