// ​
// 题目链接：K-鬼雕神刀·龙雩集舞刀法_河南萌新联赛2026第（五）场：信息工程大学

// 题目大意：在区间 [L, R] 内，找一个数 x，让它的“所有因子之和”除以 x 的商最大。

// 题目思路：

// 1. 预处理：用筛法算出 [1, R] 内每个数的因子和 σ(x)（O(nlogn)）
// 2. 查询：遍历 [L, R]，计算每个数的强度 σ(x)/x，取最大值
// 3. 输出：保留足够精度

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int sigma[MAXN + 5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, R;
    cin >> L >> R;

    // 筛法求因子和
    for (int d = 1; d <= R; d++)
    {
        for (int multiple = d; multiple <= R; multiple += d)
        {
            sigma[multiple] += d;
        }
    }

    // 找最大值
    double ans = 0;
    for (int x = L; x <= R; x++)
    {
        ans = max(ans, (double)sigma[x] / x);
    }

    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}