​// 题目链接：https://codeforces.com/contest/2240/problem/A

// 题目大意：

// 给你两个数 n 和 k。
// 你要构造 k 个非负整数（也就是 a₁, a₂, …, aₖ），要求：

// 你只需要输出这个最大的  中1的总个数。

// 题目思路：

// 因为每个数贡献的“得分”都是 1，所以优先选最小的（1、2、4、8……），这样能用有限的总和 n 买到最多的个数。

// 代码如下：

#include <bits/stdc++.h>
    using namespace std;
// #define int long long
#define endl "\n"

void solve()
{

    int n, k;
    cin >> n >> k;

    int ans = 0;  // 总共能买到多少个 1
    int coin = 1; // 当前买的硬币面值：1, 2, 4, 8, ...

    while (coin <= n)
    {
        int canBuy = n / coin;    // 当前剩余钱最多能买多少个 coin
        int buy = min(canBuy, k); // 但每个盒子最多只能买一个
        ans += buy;               // 每买一个 coin 就得到 1 个 1
        n -= buy * coin;          // 花掉钱
        coin *= 2;                // 买下一个面值
    }
    cout << ans << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
