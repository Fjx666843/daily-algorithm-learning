// ​ 题目链接：https : // codeforces.com/contest/2238/problem/A

//  题目大意：给定两个数组a，b，现在我们需要对a数组进行以下两个操作让其变为b数组
//  -选择a[i](1 <= i <= n)，使得a[i] 变为a[i] - 1,所耗费时间为1s
//  - 对a数组进行任意方式进行重新排列，所耗费时间为Cs
//  现在要我们求出最少耗费时间，如果没有合理方案则输出- 1 
     
//  题目思路：
//  我们可以先判断是否存在合法方案，那么我们可以对a，b数组进行排序，在排序之前我们定义c，d两个数组记录未排序的a，b数组，只要a数组中有任意一个元素是小于b中对于下标元素，那么就一定不合法，反之则一定存在合法方案，接着我们，就可以分情况对ans计数了，必须要排列是一种情况，不需要排列和可能排列又是一种情况（取最小值）

// 代码如下：
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl "\n"
void solve()
{
    int n, c;
    cin >> n >> c;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    vector<int> c1(n), d(n);
    c1 = a;
    d = b;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < n; i++)
    {
        if (a[i] < b[i])
        {
            cout << -1 << endl;
            return;
        }
    }
    int ans = 0;
    int flag = true;
    for (int i = 0; i < n; i++)
    {
        if (c1[i] > d[i])
        {
            ans += (c1[i] - d[i]);
            continue;
        }
        if (c1[i] < d[i])
        {
            flag = false;
            break;
        }
    }
    // cout<<ans<<endl;
    // cout<<"flag: "<<flag<<endl;
    if (flag)
    {
        int ans2 = 0;
        for (int i = 0; i < n; i++)
        {
            ans2 += (a[i] - b[i]);
        }
        int res = min(ans2 + c, ans);
        cout << res << endl;
    }
    else
    {
        int ans2 = 0;
        for (int i = 0; i < n; i++)
        {
            ans2 += (a[i] - b[i]);
        }
        cout << ans2 + c << endl;
    }
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