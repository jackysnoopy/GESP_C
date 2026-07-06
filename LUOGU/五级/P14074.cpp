#include <iostream>
#include <utility>

using namespace std;

// 使用类型别名简化代码
using ll = long long;
// info 类型用于存储 {数量, 总和}
using info = pair<ll, ll>;

// 计算不大于 n 的最大 2 的幂次
ll offset(ll n)
{
	ll res = 1;
	while ((n >> 1) >= res)
	{
		res <<= 1;
	}
	return res;
}

// 处理递归边界和完整的 2^k - 1 区间
info baseCase(ll n, ll p)
{
	// n=0 的情况
	if (n == 0)
	{
		// 0 有 0 个 '1' (偶数)，所以 p=0 时数量为 1, p=1 时数量为 0
		return make_pair(1 - p, 0);
	}
	// n=1 的情况
	if (n == 1)
	{
		// 0 (偶), 1 (奇)。p=1 时返回 {1, 1}, p=0 时返回 {1, 0}
		return make_pair(1, p);
	}
	// n = 2^k - 1 的情况，使用数学公式直接计算
	return make_pair((n + 1) / 2, n * (n + 1) / 4);
}

// 核心递归函数 (数位DP)
// 计算 [0, n] 中二进制'1'个数奇偶性为 p 的数的 {数量, 总和}
info fun(ll n, ll p)
{
	// 递归到小区间，直接用 baseCase 处理
	if (n <= 1)
	{
		return baseCase(n, p);
	}
	// 获取最高位 x (例如 n=38, x=32)
	ll x = offset(n);
	
	// a: [0, x-1] 区间的结果。这些数的最高位都为 0。
	//    我们直接用公式计算奇偶性为 p 的结果。
	info a = baseCase(x - 1, p);

	// b: [x, n] 区间的结果。这些数的最高位都为 1。
	//    我们将问题转化为求解 [0, n-x] 区间，但奇偶性要求翻转 (1-p)。
	info b = fun(n - x, 1 - p);
	
	// 合并两部分结果
	// 数量 = a 的数量 + b 的数量
	// 总和 = a 的总和 + b 的子问题总和 + b 中每个数都要加上的高位 x
	return make_pair(a.first + b.first, a.second + b.second + x * b.first);
}

int main()
{
	// 加速输入输出
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll l = 0;
	ll r = 0;
	cin >> l >> r;

	// 要求 [l, r] 区间内 '1' 为奇数的数字总和
	// 等于 solve(r) - solve(l-1)
	// fun(r, 1).second 计算 [0, r] 中'1'为奇数个数的数字总和
	// fun(l - 1, 1).second 计算 [0, l-1] 中'1'为奇数个数的数字总和
	cout << fun(r, 1).second - fun(l - 1, 1).second << '\n';

	return 0;
}
