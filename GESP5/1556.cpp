#include <iostream>
using namespace std;
/**
 * @file 1556
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-11-25
 */
int main() {
 // Type your code here
 int n;
 long long count=0;
 cin>>n;
 vector<int> ys(n+1,2);
 ys[1]=1;
 for(int i=2;i<=n;i++)
{
    for(int j=i+i;j<=n;j+=i){
        ys[j]++;
    }
}
for(int i=1;i<=n;i++){
    count+=ys[i];
}
cout<<count<<endl;
  return 0;
}