// ​
// 题目链接：C-传染病统计_2021辽宁省大学生程序设计竞赛（正式赛）

// 题目大意：
// 街上有 N 个人，编号为 1 ∼N 。简单起见，我们把每个人都看成一条线上的一个点。对每个合法的 i，第 i 个人的位置是x[i],这些人当中恰好有一个感染了 COVID-19，只有2个人的距离不超过2，才会相互感染，求出最终被感染的人数的最小和最大可能的值，也就是最好和最坏情况下这个数的值。

// 题目思路：由于数据范围较小，我们可以使用暴力枚举加标记数组来完成，因为每个人的位置是确定的，我们可以先sort再枚举，具体的可以枚举每个人作为感染者，再分别统计其他人（前面的人和后面的人）是否可以被感染即可，最后记录最大ans和最小ans即可

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
bool cnt[11];
void solve()
{
    int n;
    cin >> n;
    int mx = 1, mn = 10;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++)
    {
        memset(cnt, false, sizeof(cnt));
        cnt[a[i]] = true;
        int ans = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            for (int k = 0; k <= 10; k++)
            {
                if (cnt[k] && k != a[j])
                {
                    if (abs(a[j] - k) <= 2)
                    {
                        ans++;
                        cnt[a[j]] = true;
                        break;
                    }
                }
            }
        }
        for (int j = i + 1; j < n; j++)
        {
            for (int k = 0; k <= 10; k++)
            {
                if (cnt[k] && k != a[j])
                {
                    if (abs(a[j] - k) <= 2)
                    {
                        ans++;
                        cnt[a[j]] = true;
                        break;
                    }
                }
            }
        }
        mx = max(mx, ans), mn = min(mn, ans);
    }
    cout << mn << " " << mx << endl;
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
