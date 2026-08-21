// ​
// 题目链接：D-Flower_Rainbow_and_Grid_牛客小白月赛136

// 题目大意：给定一个n*m的网格，对于第i行第j列的方格的值是i*i-j*j,求出网格中前k大的数字之和

// (对于每个测试文件n，m之和不超过5e4)

// 题目思路：

// 网格中第 i 行第 j 列的值为：i^2 - j^2，观察可知：每行从左到右递减（j 越大值越小，问题转化为：求所有 n*m 个值中前 k 大的和，那么我们可以二分一个阈值 x，统计所有 >= x 的数的个数和总和，如果个数 >= k，说明阈值可以更大；否则阈值需要更小，对于第 i 行，需要统计满足 i^2 - j^2 >= x 的 j 的个数即 j^2 <= i^2 - x，所以 j <= sqrt(i^2 - x)然后利用等差数列公式 O(1) 计算该行的和

// 计算最终答案：

// 1. 先统计所有 > aim 的数（即 >= aim + 1）

// 2. 还需要补足 (k - cnt) 个等于 aim的数

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
pair<int, int> check(int x, int n, int m)
{
    int cnt = 0, sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int max_j_sq = i * i - x;
        if (max_j_sq < 1)
        {
            continue;
        }
        int max_j = sqrt(max_j_sq);
        max_j = min(max_j, m);
        if (max_j >= 1)
        {
            cnt += max_j;
            sum += max_j * (1LL * i * i) - max_j * (max_j + 1) * (2 * max_j + 1) / 6;
        }
    }
    return {cnt, sum};
}
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    int l = -1e10, r = 1e10;
    int aim = l;
    // 1 2 3 4
    while (l <= r)
    {
        int mid = (l + r) / 2;
        pair<int, int> res = check(mid, n, m);
        if (res.first >= k)
        {
            aim = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    pair<int, int> res = check(aim + 1, n, m);
    int ans = res.second + (k - res.first) * aim;
    cout << ans << endl;
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