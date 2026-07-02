#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MOD=1e9+7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    vector<int> pref(n+1,0);
    for(int i=0;i<n;i++) pref[i+1]=pref[i]+(s[i]-'0');
    while(q--){
        int l,r,k;
        cin>>l>>r>>k;
        l--; r--;
        int ones=pref[r+1]-pref[l];
        int zeros=(r-l+1)-ones;
        long long ALFRXORXOR=0;
        long long pw=1;
        for(int i=0;i<k;i++){
            if(i<zeros && i<ones){
                ALFRXORXOR=(ALFRXORXOR+pw)%MOD;
            }
            pw=pw*2%MOD;
        }
        cout<<ALFRXORXOR<<"\n";
    }
    return 0;
}
