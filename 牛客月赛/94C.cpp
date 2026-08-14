// ​
// 题目链接：https://ac.nowcoder.com/acm/contest/82957/C

// 题目大意：给你一个正整数数组，你可以无限次合并相邻的两个数（把它们相加变成一个数）。最后数组里最大值减最小值的差（极差）最大能是多少？

// 题目思路：我们可以知道ans=mx-mn，其中mx是最终数组的最大值，mn是最终数组的最小值，由于mn在原数组中一定是不变的，所以我们枚举每一个mn，并且求出每个位置的前缀和和后缀和，其中最大mx就在这两个和中，最后统计最大ans即可

// ​
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    int a[n + 1];
    int pre[n + 1];
    pre[0] = 0;
    a[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int mn = a[i];
        int mx = max(pre[i - 1], pre[n] - pre[i]);
        // cout << mx << endl;
        ans = max(ans, mx - mn);
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
