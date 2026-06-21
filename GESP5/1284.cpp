#include <iostream>
#include <map>
using namespace std;
/**
 * @file 1284
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-11-25
 */
map <int, int> mp;
void zyfj(int n){
    for(int i=2;i*i<=n;i++){
        while(n%i==0){
            mp[i]++;
            n/=i;

        }
        
    }
    if(n>1) mp[n]++;
}
 int main() {
 // Type your code here
 int n;
 cin>>n;
 zyfj(n);
 int num=mp.size();
 for(auto i:mp){
    cout<<i.first;
    if(i.second>1) cout<<"^"<<i.second;
    if(num>1){
        cout<<" * ";
    }
    num--;
 }
cout<<endl;

  return 0;
}