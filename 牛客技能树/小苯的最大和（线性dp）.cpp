// ​
// 题目链接：https://www.nowcoder.com/practice/c88383720c18407197547c174d902315?channelPut=tracker3

// 题目大意：给定一个数组a，

// 你有两种操作：



// 两种操作都可以执行任意次，目标是让剩余数字的总和最大。

// 题目思路：保留下来的任意两个元素之间，被删除的元素个数不能是 1（即下标差不能为 2），否则那个单独的元素无法被任何操作删除。

// 所以，这道题就转化成了：


// 我们定义：


// 那么状态转移方程就是

// //dp[i-1]+a[i]表示选择当前元素，dp[i-2]和dp[i-3]表示不选当前元素，对应操作1，2
//         dp[i] = max({dp[i - 1] + a[i], dp[i - 2], dp[i - 3]});
// 边界条件是：dp[1]=a[1]

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
const int N = 2e5 + 5;
int dp[N]; // dp[i]表示前i个元素中，可获得的最大总和（满足相邻元素下标差不为2）
void solve()
{
    int n;
    cin >> n;
    int a[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    dp[1] = a[1];
    for (int i = 2; i <= n; i++)
    {
        // dp[i-1]+a[i]表示选择当前元素，dp[i-2]和dp[i-3]表示不选当前元素，对应操作1，2
        dp[i] = max({dp[i - 1] + a[i], dp[i - 2], dp[i - 3]});
    }
    cout << dp[n] << endl;
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
