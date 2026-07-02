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
        vector<int> l1(n),r1(n),l2(n),r2(n);
        for(int i=0;i<n;i++) cin>>l1[i]>>r1[i]>>l2[i]>>r2[i];
        int minVal=1e9,maxVal=0;
        for(int i=0;i<n;i++){
            minVal=min(minVal,l2[i]);
            maxVal=max(maxVal,r2[i]);
        }
        cout<<maxVal-minVal+1<<"\n";
    }
    return 0;
}
