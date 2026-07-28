// ​题目链接：https://www.nowcoder.com/practice/1ae49fb83b3f404f89dc0933bb8a0694?channelPut=tracker3

// 题目大意：小红位于一个 n×m矩阵的左上角，她每次只能向下或向右走一格。她想知道，要想到达矩阵的右下角，总共有多少种走法？由结果可能很大，请输出对 998244353998244353 取模后的值（1<=n,m<=1000）

// 题目思路：我们可以通过动态规划来解决这道题目，首先先定义状态dp[i][j]表示：从起点（1，1）走到（i，j）有多少种不同的走法;接着找到状态转移方程：要想到达（i，j），只有通过以下两种方式：向下走一格（i-1，j）->（i，j）和向右走一格（i，j-1）->（i，j）,所以dp[i][j]=dp[i-1][j]+dp[i][j-1],也就是到达 (i,j) 的走法数 = 到达上面格子的走法数 + 到达左边格子的走法数;最后确定边界条件：

// 代码如下

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
const int mod = 998244353;
const int N = 1005;
int dp[N][N]; // dp[i][j]表示：从起点（1，1）走到（i，j）有多少种不同的走法
void solve()
{
    int n, m;
    cin >> n >> m;
    dp[1][1] = 1;
    for (int i = 1; i < N; i++)
    {
        dp[1][i] = 1;
    }
    for (int i = 1; i < N; i++)
    {
        dp[i][1] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if ((i == 1 && j == 1) || i == 1 || j == 1)
                continue;
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
        }
    }
    cout << dp[n][m];
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin>>T;
    while (T--)
    {
        solve();
    }
    return 0;
}
