​ // 题目链接：https://codeforces.com/contest/2237/problem/A

    // 题目大意：存在n座高塔，我们需要在每座高塔进行如下操作：

    // 爬上第i座高塔，向右射击，将击倒的第一座高塔削到与第i座高塔同等高度

    // 现在要我们求出塔楼高度的最终和的最小值

    // 题目思路：可以知道，如果右边的高塔低于左边的高塔，那么就不会做出贡献，同理，左边的高塔高于右边的高塔也不会做出贡献，所以我们只需要统计递增的子数组所做出的贡献即可

    // 代码如下：

​#include<bits / stdc++.h> using namespace std;
// #define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    int a[n] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++)
    {
        if (a[i] > a[i - 1])
        {
            a[i] = a[i - 1];
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        res += a[i];
    }
    cout << res << endl;
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
