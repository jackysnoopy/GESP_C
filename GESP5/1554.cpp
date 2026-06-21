#include <iostream>
#include <map>
using namespace std;
/**
 * @file 1554
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
 if(n==1){
    cout<<"0 0"<<endl;
    return 0;
 }
 else{
    for(int i=2;i<=n;i++){
        zyfj(i);
    }

 }
 for(auto i:mp){
    cout<<i.first<<" "<<i.second<<endl;
 }

  return 0;
}