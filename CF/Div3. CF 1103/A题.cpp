​ // 题目链接：https://codeforces.com/contest/2236/problem/A

    // 题目大意：给定一个数组h，现在要求我们给每个h[i]增加x，使得每个h[i]相等，其中1<=x<=k,求出k的最小值

    // 题目思路：我们可以找到h数组中的最大值ma和最小值mi，可以知道，最终数组的可能最小值一定是当前ma+1，那么k=ma-mi

    // 代码如下：

​#include<bits / stdc++.h> using namespace std;
// #define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    int h[n + 1];
    int ma = 0;
    int mi = 7;
    for (int i = 1; i <= n; i++)
    {
        cin >> h[i];
        ma = max(h[i], ma);
        mi = min(h[i], mi);
    }
    ma++;
    int res = ma - mi;
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
