// ​
// 题目链接：https://codeforces.com/gym/105911/problem/F

// 题目大意：

// 有一头龙，接下来 n 天要控制饮食。每天有两个量：



// 它们之间满足递推关系：

// c[i]=p×c[i−1]+(1−p)×r[i−1]

// 也就是说，今天的代谢量，一部分取决于昨天的代谢量，另一部分取决于昨天吃了多少。

// 初始值：r₀ 和 c₀ 是已知的（第 0 天的状态，作为递推起点）。

// 约束：




// 目标：合理安排所有非放纵日的 r_i，使得 n 天的总收益最大：max Σ (c[i] - r[i])   (i = 1 到 n)

// 题目思路：根据题目给定的递推公式可以guess r[i]越小，答案越大，让所有可以选择的r[i]取L即可

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
#define int long long
#define endl "\n"

void solve()
{
    int n, k;
    cin >> n >> k;
    double r0, c0, P, L, R;
    cin >> r0 >> c0 >> P >> L >> R;
    vector<double> r(n + 1, 0), c(n + 1, 0);
    vector<bool> is_fixed(n + 1, false);
    for (int i = 0; i < k; i++)
    {
        int day;
        double val;
        cin >> day >> val;
        r[day] = val;
        is_fixed[day] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!is_fixed[i])
        {
            r[i] = L;
        }
    }
    r[0] = r0;
    c[0] = c0;
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        c[i] = P * c[i - 1] + (1 - P) * r[i - 1];
        ans += c[i] - r[i];
    }
    cout << fixed << setprecision(10) << ans << endl;
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