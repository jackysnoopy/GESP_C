#include <vector>
#include <iostream>

using namespace std;
/**
 * @file FILENAME
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-10-24
 */
int main()
{
  // Type your code here
  vector<int> vec = {1, 2, 3, 4};
  cout << vec.capacity() << endl;//4
  vec.insert(vec.begin() + 3, 5);//1 2 3 5 4
  vec.insert(vec.begin() + 2, {6, 7});///1 2 6 7 3 5 4
  vec.erase(vec.begin() + 2);//1 2 7 3 5 4
  cout << vec.front()<<" "<< vec.back() <<endl;
  for (auto i : vec)
    cout << i << " ";
  cout << endl;
  cout<<vec.at(4)<<endl;//5
  cout << vec.size() << endl;//6
  cout << vec.capacity() << endl;//8
  vec.shrink_to_fit();//收缩容量
  cout << vec.capacity() << endl;//6
  return 0;
}