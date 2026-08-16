// ​
// 题目链接：https://ac.nowcoder.com/acm/contest/139206/D

// 题目大意：在给定高度数组 h[1..n] 中，找一个最长的连续子数组 [l, r]，使得该区间内相邻元素绝对差之和（即起伏值）不超过 k。

// 题目思路：根据h数组求出对应的差分数组d后，我们使用双指针线性遍历寻找最大合法区间即可

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
const int N = 2e5 + 10;
int d[N];
void solve()
{
    int n, k;
    cin >> n >> k;
    int h[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> h[i];
    }
    d[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        d[i] = abs(h[i] - h[i - 1]);
    }
    int l = 1, r = 1, sum = 0;
    sum = d[1];
    int ans = r - l + 1;
    while (r < n)
    {
        r++;
        while (l < r && sum + d[r] > k)
        {
            sum -= d[l + 1];
            l++;
        }
        sum += d[r];
        ans = max(ans, r - l + 1);
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
