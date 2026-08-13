​
    // 题目链接：https://ac.nowcoder.com/acm/contest/17624/K

    // 题目大意：你需要用 1 到 n 的所有整数（每个恰好用一次）排成一个序列。如果序列中某个位置 i 满足 后一个数 = 前一个数 + k，就算一个“好对”。你的目标是让这样的“好对”数量尽可能多，然后输出这个序列。

    // 题目思路：把数按模 k 分组，每组升序排好，再按组顺序拼接，就能让同一组内的相邻对全都满足差 k，总数达到最大。

    // 代码如下：

​#include<bits / stdc++.h> using namespace std;
#define int long long
#define endl "\n"

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> ans;

    // 按余数 1..k 分组输出（余数 0 对应 k）
    for (int r = 1; r <= k; r++)
    {
        for (int x = r; x <= n; x += k)
        {
            ans.push_back(x);
        }
    }

    // 输出，注意行末无空格
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << '\n';
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
