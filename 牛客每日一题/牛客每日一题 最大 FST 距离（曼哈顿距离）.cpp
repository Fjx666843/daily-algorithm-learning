​
题目链接：最大 FST 距离_牛客题霸_牛客网

题目大意：给定 n 个元素，第 i 个元素具有特征值 A[i]​。定义FST 距离如下：

dist(i,j)=∣i^2−j^2∣+∣A[i]^2−A[j]^2∣

请计算 A[i]​ 中所有元素对儿中的最大 FST 距离。

题目思路：暴力求法很容易想到，但是O(n^2)必然超时，通过观察可以发现：

令 B[i]=i^2，C[i]=A[i]^2

则 dist(i,j)=∣B[i]−B[j]∣+∣C[i]−C[j]∣

这是二维平面上的曼哈顿距离,其中每个点 i 的坐标是 (B[i],C[i])=(i^2,A[i]^2)

曼哈顿距离的最大值可以通过以下方式计算：

对于曼哈顿距离 ∣x[i]−x[j]∣+∣y[i]−y[j]∣，最大值等于：
max⁡(x[i]+y[i])−(x[j]+y[j]),(x[i]−y[i])−(x[j]−y[j])

推到过程如下：

绝对值 |a - b| 等于 max(a-b, b-a)

所以 |x₁ - x₂| + |y₁ - y₂| 可以展开成4种情况：

情况1: (x₁ - x₂) + (y₁ - y₂) = (x₁+y₁) - (x₂+y₂)
情况2: (x₁ - x₂) - (y₁ - y₂) = (x₁-y₁) - (x₂-y₂)
情况3: -(x₁ - x₂) + (y₁ - y₂) = -(x₁-y₁) + (x₂-y₂)
情况4: -(x₁ - x₂) - (y₁ - y₂) = -(x₁+y₁) + (x₂+y₂)

即：




代码如下：

​#include <bits/stdc++.h>
using namespace std;
using in128 = __int128_t;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    int max_sum = LLONG_MIN, min_sum = LLONG_MAX;
    int max_diff = LLONG_MIN, min_diff = LLONG_MAX;

    for (int i = 1; i <= n; i++)
    {
        int x = i * i;
        int y = a[i] * a[i];

        max_sum = max(max_sum, x + y);
        min_sum = min(min_sum, x + y);

        max_diff = max(max_diff, x - y);
        min_diff = min(min_diff, x - y);
    }

    int ans = max(max_sum - min_sum, max_diff - min_diff);
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}