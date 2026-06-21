#include <iostream>
#include <vector>

using namespace std;

long long fibonacci(int n) {
  if (n < 0) {
    return -1;
  }

  if (n == 0) {
    return 0;
  }

  if (n == 1) {
    return 1;
  }

  vector<long long> dp(n + 1);
  dp[0] = 0;
  dp[1] = 1;

  for (int i = 2; i <= n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

int main() {
  int n;
  cout << "请输入一个非负整数 n: ";
  cin >> n;

  long long result = fibonacci(n);
  if (result == -1) {
    cout << "输入无效，n 不能为负数。" << endl;
    return 1;
  }

  cout << "斐波那契数列第 " << n << " 项是: " << result << endl;
  return 0;
}
