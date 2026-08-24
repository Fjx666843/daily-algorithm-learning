// ​
// 题目链接：L-神秘数字_河南萌新联赛2026第（六）场：郑州大学

// 题目大意：msj给定一个正整数n，神秘数字x>=1&&x<=n，我们可以构造出若干集合，对于每个集合msj会如实回答x是否该集合中，求出可以找到x的最少集合的数目构造方案

// 题目思路：这是一道典型的毒酒问题，我们可以通过二进制来解决这个问题，具体分析如下：对于每个集合我们可以看为二进制的每一位，那么我们至少需要的二进制位数是m=log2(n),因为2^m必须>=n，如果<n,那么无法有效推断，其中m就是我们需要找到x的最少集合的数目，这里m的最大值是不超过15的，因为n最大才1e5，至于对于每个集合如何求，对于每个集合我们可以从1开始枚举到n，如果(x&(1<<bit)),那么说明x是该集合需要的数字，因为只有当二进制位同1时该位才可能为答案做出贡献，也就是第i个集合包含所有第i位为1的数字，类似第i个犯人品尝所有第i位为1的酒

// 代码如下：时间复杂度O(15*n)

// ​
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    int m = ceil(log2(n));
    cout << m << endl;
    for (int bit = 0; bit < m; bit++)
    {
        vector<int> ans;
        for (int x = 1; x < n; x++)
        {
            if (x & (1 << bit))
            {
                ans.push_back(x);
            }
        }
        cout << ans.size();
        for (auto i : ans)
        {
            cout << " " << i;
        }
        cout << endl;
    }
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