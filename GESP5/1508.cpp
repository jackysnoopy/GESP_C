#include <vector>
#include <iostream>
using namespace std;
/**
 * @file 1508
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-11-25
 */
const int MAX=10e6;
vector<bool> luck(MAX+1,false);
vector<int> next_luck(MAX+1,0);
int main() {
 // Type your code here
 int a,N;
 cin>>a>>N;
 for(int i=1;i*i<=MAX;i++){
  if(i*i>=a){
    luck[i*i]=true;
    for(int j=2*i*i;j<=MAX;j+=i*i){
        luck[j]=true;
    }
  }
 }
 for(int i=MAX;i>=1;i--){
    next_luck[i]=luck[i]?i:next_luck[i+1];
 }
 for(int i=0;i<N;i++){
    int x;
    cin>>x;
    luck[x]?cout<<"lucky"<<endl:cout<<next_luck[x]<<endl;
 }


  return 0;
}